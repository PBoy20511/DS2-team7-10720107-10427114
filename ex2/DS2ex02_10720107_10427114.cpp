//10427114 熊觀一 HSIUNG KUAN I 請助教下載GitHub版本評分
//10720107 陳丕中 CHEN PI ZHONG

//*******************************/
//Heaader file for School List by YH 
//*******************************/

using namespace std ;           // standard neming space

#include <iostream>             //cout, endl
#include <fstream>              //open, is_open
#include <string>               //string
#include <vector>               //vector
#include <cstdlib>              //atoi, system
#include <iomanip>              //setw, setprecision
#include <queue>                //BST Tree Use

#include <stack>                //push, pop, top
#define PTR_NUM 3
#define KEY_NUM PTR_NUM - 1

//************ read data ***********//

typedef struct sT {
    string  sname ;         // school name
    string  dname ;         // department name
    string  type ;          // either day or night
    string  level ;         // graduate or undergraduate
    int     nstud ;         // number of graduation students
    int     nprof ;         // number of professors
    int     ngrad ;         // number of graduates
} schoolType ;              // structure of school data

class SchoolList {

    vector<schoolType> allR ;   // list of all recodes with 7 columns
    string fileID ;             //file identifier

    //*******************************/
    //The above are private data members
    //*******************************/
    void reset() ;              //dsclaretion: inital set up
    //*******************************/
    //The above are private methods
    //*******************************/
public:
    SchoolList() { reset() ; }      // constructor for initialization
    ~SchoolList() { reset() ; }     // destructor for initialization
    //*******************************/
    //The above are private methods
    //*******************************/
    bool readFile() ;                // declartion: read all from a file
    void printFile() ;               // print file to the screen
    vector<schoolType> getFile() { return allR ; }  

}; //end SchoolList

    //*******************************/
    //class SchoolList declaretion is as the above
    //*******************************/

void SchoolList::reset()
{
    this->allR.clear();
    this->fileID.clear();
}   //end reset
    //*******************************/
    //The above are definitions of private methods
    //*******************************/

bool SchoolList::readFile()         //definition: read all from a file
{
    fstream inFile ;                //file headle
    string fileName ;               //file name

    this->reset() ;                 //call: initial set up
    cout << endl << "Input a file namber: " ;   
    cin >> this->fileID ;           //get the file identifier
    fileName = "input" + fileID + ".txt" ;
    inFile.open(fileName.c_str(),fstream::in) ; //open file to read
    if (!inFile.is_open()) {                    // unable to open file
        cout << endl << "### " << fileName << "does not exist! ###" << endl ;
        return false ;
    } //end if
    else {
        char cstr[255] ;                        //input buffer of one line as c-string
        int fNo, pre, pos ;

        inFile.getline(cstr,255,'\n') ;         //skip the 1st header line
        inFile.getline(cstr,255,'\n' );         //skip the 2bd header line
        inFile.getline(cstr,255,'\n') ;         //skip the list of column name
        while (inFile.getline(cstr,255,'\n')){  //get all records line by line
            schoolType oneR ;                   //one data record
            string buf, cut ;                   //transform c-string into C++ string

            fNo = 0 ;                           //number of fields read so far
            pre = 0 ;                           //locate one field of input record
            buf.assign(cstr) ;                  //copy c-string into C++ string

            do {                                //scan the buffer from left to right
                pos = buf.find_first_of('\t',pre) ;     //locate the next field by '\t'(tab)
                cut = buf.substr(pre,pos-pre) ;         //retrieve a field
                switch(++fNo){
                    case 2: oneR.sname = cut ;          //get the school name
                        break ;
                    case 4: oneR.dname = cut ;          //get the department name
                        break ;
                    case 5: oneR.type = cut ;           //get either day or night
                            break ;
                    case 6: oneR.level = cut ;          // get graduate or undergraduate
                            break ;
                    case 7: oneR.nstud = atoi(cut.c_str()) ;    // get the number of students
                        break ;
                    case 8: oneR.nprof = atoi(cut.c_str()) ;    // get the number of professors
                        break ;
                    case 9: oneR.ngrad = atoi(cut.c_str()) ;    // get the number of graduates
                        break ;
                    default: break ;
                } //end seitch

                pre = ++pos ;                       //move to the next field
            } while ((pos>0)&&(fNo <10)) ;          //continue if there are still fields to be read

            this->allR.push_back(oneR) ;            //save one record into the school list
        } //end outer-while

        inFile.close();                             //close file
    } // end else

    if (!this->allR.size()) {
        cout << endl << "### Get nothing from the file" << fileName << "!###" << endl ;
        return false ;
    } // end if

    return true ;
} // end readFile

void SchoolList::printFile() {

    for ( int i = 0 ; i < allR.size() ; i++ ) {
        cout << i + 1 << '\t';
        cout << allR[i].sname << "\t" << allR[i].dname <<  "\t" ;
        cout << allR[i].type << "\t" << allR[i].level << "\t" ;
        cout << allR[i].nstud << "\t" << allR[i].nprof << "\t" ;
        cout << allR[i].ngrad << endl;
    } // end for

} // end printFile

//************ mission type ***********//



//************* mission 1 *************//



typedef struct CT {
	string nameSchool ; // All the content from the school
	string nameMajor ;
	string division ;
	string level ;
	int numStudent ;
	int numTeacher ;
	int numGraduate ; // number of graduates
	
	int numOrder ; // whatplace
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
        	int tempOrder = 1 ;
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
        		aCollege.numOrder = tempOrder ;
        	
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
            	tempOrder++ ;
            
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

struct TreeNode{ // store 2-3 Tree's deta
	vector< CollegeType > itemOne ;
	vector< CollegeType > itemTwo ; // deta
	
	vector< CollegeType > itemTemp ;
	
	
	TreeNode *left ;
	TreeNode *down ;
	TreeNode *right ; // pointer
	
	TreeNode *tempPointer ; 
	
	TreeNode *parent ; // parent
};

class Tree{
	TreeNode *head ;
	
	Tree(){
		head = NULL ;
	} 
	~Tree(){
	}
	
	bool IsEmpty(){
		if( head == NULL ){
			return true ;
		} // if
		else{
			return false ;
		}
	} // IsEmpty
	
	bool IsItemOneBigger( TreeNode node ){ // find out ids item one bigger
	    if( node.itemOne[0].nameSchool > node.itemTwo[0].nameSchool ){
	    	return true ;
		} // if
		else{
			return false ;
		} // else
	} // IsIsItemOneBigger
	
	bool Search( string name, TreeNode* &walk ){ // find
        while( walk != NULL ){
        	if( HowManyItems == 1 ){ // if we only need to check itemOne
        		if( walk->itemOne[0].nameSchool == name ){ // if we find it, set theThing to that item(vector)
       				return true ;
				} // if
				else if( walk->itemOne[0].nameSchool > name ){
					walk = walk->right ;
				} // if
				else if( walk->itemOne[0].nameSchool < name ){
					walk = walk->left ;
				} // else if
			} // if 
			else{ // if we need to check both item
        		if( walk->itemOne[0].nameSchool == name ){ // if we find it, set theThing to that item(vector)
        			return true ;
				} // if
				else if( walk->itemTwo[0].nameSchool == name ){ // if we find it, set theThing to that item(vector)
					return true ;
				} // else if
				else if( IsItemOneBigger( walk ) ){ // ItemOne Bigger
				    if( walk->itemOne[0].nameSchool < name ){
				    	walk = walk->right ;
					} // if
					else if( walk->itemTwo[0].nameSchool > name ){
						walk = walk->left ;
					} // else if
					else{
						return false ; // means that there's no same name in the node
					} // else
				} // if
				else if( !IsItemOneBigger( walk ) ){ // ItemTwo Bigger
				    if( walk->itemTwo[0].nameSchool < name ){
				    	walk = walk->right ;
					} // if
					else if( walk->itemOne[0].nameSchool > name ){
						walk = walk->left ;
					} // else if
					else{
						return false ; // means that there's no same name in the node
					} // else
				} // else if

			} // else 
				
		} // while
		
		return false ;
		
	} // Search
	
	int HowManyItems( TreeNode *leaf ){ // find out how many item you have
	
		if( leaf->item1 != NULL ){ // the first one has item
			
			if( leaf->right != NULL ){ // the second one has item 
				return 2 ;
				
			} // if
			else{
				return 1 ;
			} // else
			
		} // if
		else{
			return 0 ;
		} // else
	} // HowManyItems
	
	void Build23Tree( ClassList list ){
		for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
          Insert23Tree( list.GetSet()[i] ) ;
		} // for
		
	} // Build23Tree
	
	/*vector<CollegeType> TheSchool( TreeNode node, string name ){ // which item is "the" item I want(used at:if already have School name )
		if( HowManyItems( node ) == 1 ){
			return node.itemOne ;
		} // if
		else{
	        if( node.itemOne[0].nameSchool == name ){
	        	return node.itemOne ;
			} // if
			else{
				return node.itemTwo ;
			} // else
		} // eise
		
	} // TheSchool
	
    void Insert23Tree( CollegeType item ){
		TreeNode* walk = head ;
        if( Scarch( item.nameSchool, walk ) ){ //if already have School name
        	TheSchool( walk, item.nameSchool )
		} // if
		else{
			
		} // else
	} // Insert
	*/
	

	
	void Insert23TreeEX( CollegeType item ){ // 給一個CollegeType
	    TreeNode* walk ;
	    if( Search( item.nameSchool, walk ) ){ // 如果有找到對應節點 
	    	
		} // if
        else{
        	
		} // else	
	} // NEW insert23tree

	void split( TreeNode leafNode, TreeNode root ){

	} // split
}; // tree



//************* mission 2 *************//

class AVLtree {         // class of AVLtree

    struct nodeType {
    
        vector<int> data_ngrad_idx;     // index to find data
        int data_ngrad ;                // number of graduate strudents
        nodeType* left;                 // left child
        nodeType* right;                // right child
        int height;                     // tree height
    }; // end nodeType

    nodeType* root;     // just a root
    int nodenum ;       // number of node

    int max(int LeftHeight, int RightHeight) {       // max(num1, num2)

        if ( LeftHeight > RightHeight )
            return LeftHeight ;
        else return RightHeight ;    

    } // end max(num1,num2)

    nodeType* insertAVL(int data_ngrad_idx, int data_ngrad, nodeType* cur) { // insert new 
    
        if(cur == NULL) {
        
            cur = new nodeType;
            cur->data_ngrad_idx.push_back(data_ngrad_idx);      // becouse same idx need put together
            cur->data_ngrad = data_ngrad;
            cur->height = 0;
            cur->left = cur->right = NULL;
            nodenum++ ;

        } // end if
        else if(data_ngrad < cur->data_ngrad) {
        
            cur->left = insertAVL(data_ngrad_idx, data_ngrad, cur->left);
            if(height(cur->left) - height(cur->right) == 2) {
            
                if(data_ngrad < cur->left->data_ngrad)
                    cur = rotateLL(cur);    // LL
                else
                    cur = rotateLR(cur);    // LR
            } // end if

        } // end else if
        else if(data_ngrad > cur->data_ngrad)
        {
            cur->right = insertAVL(data_ngrad_idx, data_ngrad, cur->right);
            if(height(cur->right) - height(cur->left) == 2)
            {
                if(data_ngrad > cur->right->data_ngrad)
                    cur = rotateRR(cur);    // RR
                else
                    cur = rotateRL(cur);    // RL
            } // end if

        } // end else if
        else if(data_ngrad == cur->data_ngrad) cur->data_ngrad_idx.push_back(data_ngrad_idx);      // becouse same idx need put together

        cur->height = max(height(cur->left), height(cur->right))+1;
        return cur;
    }

    nodeType* rotateLL(nodeType* &curX) {       //singleRightRotate
    
        nodeType* curY = curX->left;
        curX->left = curY->right;
        curY->right = curX;
        curX->height = max(height(curX->left), height(curX->right))+1;
        curY->height = max(height(curY->left), curX->height)+1;
        return curY;
    } // end rotateLL

    nodeType* rotateRR(nodeType* &curX){         //singleLeftRotate 
    
        nodeType* curY = curX->right;
        curX->right = curY->left;
        curY->left = curX;
        curX->height = max(height(curX->left), height(curX->right))+1;
        curY->height = max(height(curY->right), curX->height)+1 ;
        return curY;
    } // end rotateRR

    nodeType* rotateRL(nodeType* &cur){         // doubleLeftRotate
    
        cur->right = rotateLL(cur->right);
        return rotateRR(cur);
    }

    nodeType* rotateLR(nodeType* &cur){         // doubleRightRotate
    
        cur->left = rotateRR(cur->left);
        return rotateLL(cur);
    }

    int height(nodeType* cur) {                 // restore tree height
    
        return (cur == NULL ? -1 : cur->height);
    } // end height

    void insertAVL(int data_ngrad_idx, int data_ngrad) {        // insert data
        root = insertAVL(data_ngrad_idx, data_ngrad, root);
    } // end insertAVL

public:
    AVLtree() {             // initialization
        root = NULL ;
        nodenum = 0 ;
    } // end AVLtree

    void creatAVLtree(std::vector<schoolType> array) {

        for (int i = 0; i < array.size(); i++) {
            insertAVL( i + 1, array[i].ngrad) ;         // input idx and data_ngrad
        } //end for

    } // end creatAVLtree

    void display(std::vector<schoolType> array) {
        
        cout << "Tree height = " << root->height + 1 << endl ;      // Tree height  Q: I don't know why always DEMO height - 1
        cout << "Number of nodes = " << nodenum << endl ;       // Number of nodes

        for (int i = 0 ; i < root->data_ngrad_idx.size() ; i++ ) {  // all data in root
            for ( int j = 0 ; j < array.size() ; j++ ) {
                
                if ( root->data_ngrad_idx[i] == j + 1 ) {
                    cout << i + 1 << ": [" << j + 1 << "] " << array[j].sname << ", " ;
                    cout << array[j].dname << ", " << array[j].type <<  ", " ;
                    cout << array[j].level << ", " << array[j].ngrad << endl ;
                } // end if

            } // for
        } // end for
 
    } // display

    void clear() {             // initialization
        root = NULL ;
        nodenum = 0 ;
    } // end clear

}; // end AVLtree

//**************** main ***************//

void msg1() {

    cout << "massage 1 please key 1" << endl ;
    cout << "massage 2 please key 2" << endl ;
    cout << "other key will end program" << endl << endl ;
    cout << "(1/2/end): " ;

} // end msg1

void msg2() {

    cout << "program will end! " << endl ;

} // end msg1


int main() {



    SchoolList ListR ;          //call the list
    AVLtree Misson2 ;
    
    string orderkey = "" ;      //contral mission (1,2,end)
    bool text = true ;          //contral Loop

    while ( text ) {
        if (ListR.readFile()) {     //read the data
            //ListR.printFile() ;   //see if bug exist
            msg1();
            cin >> orderkey ;            
            if ( orderkey == "1" ) {            // mission 1
                // not yet
            } // end if
            else if ( orderkey == "2" ) {       // mission 2
				Misson2.creatAVLtree(ListR.getFile()) ;
                Misson2.display(ListR.getFile()) ;
                Misson2.clear() ;
            } // end elseif
            else { msg2(); text = false ; }     //end the Loop
        
        } // end if
	
    } // end while


    system("pause");
    return 0 ;
}
