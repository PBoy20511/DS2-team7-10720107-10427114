// 10720107 陳丕中 10427114 熊觀一 

#include<iostream> 
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>


using namespace std ;

typedef struct CT {
	string nameSchool ; // All the content from the school
	string nameMajor ;
	string division ;
	string level ;
	int numStudent ;
	int numTeacher ;
	int numGraduate ; // number of graduates
} CollegeType ; 

class ClassList{
		
	vector< CollegeType > collegeSet ; 
	
	
	public:
		
	ClassList(){
		
	} // ClassList
	~ClassList(){
		ClearList() ;
	}
	
	bool Load( string fileName ) { 
	// 讀入資料
	 
    	FILE *infile = NULL ;
    	bool success = false ;
    	fileName = "input" + fileName + ".txt" ;
    	infile = fopen(fileName.c_str(), "r" ) ;

		if ( infile == NULL )
			;
		else{

        	char tempChar ;
        	for ( int i = 0 ; i < 3 ; i++ )
        		while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' )
            		;

        	CollegeType aCollege ;
        	aCollege.nameSchool = "" ;
        	aCollege.nameMajor = "" ;
        	aCollege.division = "" ;
        	aCollege.level = "" ;
        	aCollege.numStudent = 0 ;
        	aCollege.numTeacher = 0 ;
        	aCollege.numGraduate = 0 ;
        
			int numTab = 0 ;
			string stringStudent = "" ;
			string stringTeacher = "" ;
			string stringGraduate = "" ;
		
        	while ( fscanf( infile, "%c", &tempChar ) != EOF ) {
        		while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' ) {
        			if ( tempChar == '\t' )
        				numTab++ ;
        			else if ( numTab == 1 )
        				aCollege.nameSchool = aCollege.nameSchool + tempChar ;
        			else if ( numTab == 3 )
        				aCollege.nameMajor = aCollege.nameMajor + tempChar ;
        			else if ( numTab == 4 )
        				aCollege.division = aCollege.division + tempChar ;
        			else if ( numTab == 5 )
        				aCollege.level = aCollege.level + tempChar ;
        			else if ( numTab == 6 )
        				stringStudent = stringStudent + tempChar ;
        			else if ( numTab == 7 )
        				stringTeacher = stringTeacher + tempChar ;
        			else if ( numTab == 8 )
        				stringGraduate = stringGraduate + tempChar ;
        		
        		} //while
        		
        		aCollege.numStudent = atoi( stringStudent.c_str() ) ;
        		aCollege.numTeacher = atoi( stringTeacher.c_str() ) ;
        		aCollege.numGraduate = atoi( stringGraduate.c_str() ) ;
        	
            	collegeSet.push_back( aCollege ) ;
            
            	aCollege.nameSchool = "" ;
	        	aCollege.nameMajor = "" ;
	        	aCollege.division = "" ;
	        	aCollege.level = "" ;
	        	aCollege.numStudent = 0 ;
	        	aCollege.numTeacher = 0 ;
	        	aCollege.numGraduate = 0 ;
	        
            	stringStudent = "" ;
            	stringTeacher = "" ;
            	stringGraduate = "" ;
            	numTab = 0 ;
            
        	} // while not EOF

        	success = true ;
        	fclose( infile ) ;

		} // else

		return success ;
	} // Load function 1 
	
	void Print() {
		for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
			cout << collegeSet[i].nameSchool << "\t" << collegeSet[i].nameMajor << "\t"
				 << collegeSet[i].division << "\t" << collegeSet[i].level << "\t" 
				 << collegeSet[i].numStudent << "\t" << collegeSet[i].numTeacher << "\t"
				 << collegeSet[i].numGraduate << "\n";
		} // for
		
	} // Print function 2
	
	vector< CollegeType > GetSet() {
		return collegeSet ;
	} // GetSet function 3
	
	void ClearList() {
	    collegeSet.clear() ;
	} // ClearList function 4
	
	void Remove( CollegeType aCollege ) {
		for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
			if ( collegeSet.at( i ).nameSchool == aCollege.nameSchool && collegeSet.at( i ).nameMajor == aCollege.nameMajor 
				  && collegeSet.at( i ).division == aCollege.division && collegeSet.at( i ).level == aCollege.level )
				collegeSet.erase( collegeSet.begin() + i ) ;
		} // for
	} // Remove function 5 
	
};

struct heapNode{
	int place ;
	int gdNum ;
};

class Heap{
	int sizeH = 0 ;
	heapNode *item;

    public:	
	Heap(){
	}
	~Heap(){
	}
	
		
	bool heapIsEmpty( ) ; 
	void heapDelete( heapNode rootCollege, int size ) ; 
	void heapRebuild( int root ) ; 
	void BuildHeap( vector<CollegeType> classSet, int size ) ; 
	void InsertHeap() ;
	void PrintM1() ;
     

};

void Heap::BuildHeap( vector<CollegeType> classSet, int size ) {

    item = new heapNode[size] ; //建立Array 
	for( int i = 0; i < size ; i ++ ){
		if( sizeH >= size )
			cout << "HeapFull" ;
			
		int place = sizeH ;
		int parent = ( place - 1 ) / 2 ;
		

		item[i].gdNum = classSet[i].numGraduate ; //  先將ClassSet的資料放入Heap最左邊 
		item[i].place = place ;

		
		while( ( parent >= 0 ) && ( item[place].gdNum > item[parent].gdNum ) ){ // 重新排順序 

           	int tempGd ;
           	// int tempPlace ;
           	tempGd = item[parent].gdNum ;
           	// tempGd = item[parent].place ;
           	item[parent].gdNum = item[place].gdNum ;
           	// item[parent].place = item[place].place ;
           	item[place].gdNum = tempGd ;
           	// item[place].place = tempPlace ;
            
			place = parent ;
			parent = ( place - 1 )/ 2 ;
		} // while
        
		
		sizeH ++ ;
	} // for
	
	cout << "<min heap>" << "\n" ;
	cout <<"["<< item[0].place <<"]" ;
	cout << item[0].gdNum ; 

	
} // BuildHeap

void Heap::heapDelete( heapNode rootItem, int size ) {
	if ( heapIsEmpty( ) )
		cout << "root Empty" ;
	else {
		rootItem = item[0] ;
		item[0] = item[size] ;
		heapRebuild(0) ;
	} // else
	
} // HeapDelete

void Heap::heapRebuild( int root ){
	int child = 2*root + 1 ;
	
	if ( child < sizeH ){
		int rightChild = child + 1 ;
		if ( (rightChild < sizeH ) && ( item[rightChild].gdNum > item[child].gdNum ) ){
			child = rightChild ;
		} // if
		else {
			heapNode temp = item[root] ;
			item[root] = item[child] ;
			item[child] = temp ;
		} // else
	} // if
	
} // heapRebuild

bool Heap::heapIsEmpty( ) {
	if ( sizeH == 0 ) {
		return true ;
	} // if
	else {
		return false ;
	}
} // heapIsEmpty()


void Heap::PrintM1(){
	
	
} // PrintM1()


int main() {
	
	ClassList classList ;
    Heap heapGrd ;
	int cmd = 0 ;
	cout << "(1)Build Heap(0)Exit\nCommand:" ;
	cin >> cmd ;
	
	while( cmd != 0 ){
		if( cmd == 1) {
			classList.ClearList() ; 
			int size = 0 ;
			cout << "File name: " ;
			string fileName ;
			cin >> fileName ;
			
			if ( classList.Load( fileName ) ) { // 讀入檔案 
			    int size = classList.GetSet().size() ; 
				heapGrd.BuildHeap( classList.GetSet() , size) ; // 建立Heap 
			} // if
			else
				cout << "File not found.\n" ;
		} // if
		else {
			cout << " There's no such code! " ;
		} // else
		
		cout << "(1)Build Heap(0)Exit\nCommand:" ;
		cin >> cmd ;
	} // whilef
} // main()




















