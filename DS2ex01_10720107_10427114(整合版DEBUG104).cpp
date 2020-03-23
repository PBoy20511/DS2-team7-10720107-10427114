//10427114 熊觀一 HSIUNG KUAN I
//10720107 陳丕中 CHEN PI ZHONG

//*******************************/
//Heaader file for School List by YH 
//*******************************/

//#ifndef _SchoolList_HPP << What wroung? can't use
//#define _SchoolList_HPP

using namespace std ;           // standard neming space

#include <iostream>             //cout, endl
#include <fstream>              //open, is_open
#include <string>               //string
#include <vector>               //vector
#include <cstdlib>              //atoi, system
#include <iomanip>              //setw, setprecision
#include <queue>                //BST Tree Use

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
//School code; School Name; Department code; Department name; Daytime training; Level;
//Number of students; Number of teachers; Graduates of the school year; County name; System type;
//學校代碼	學校名稱	科系代碼	科系名稱	日間∕進修別	等級別	學生數	教師數	上學年度畢業生數	縣市名稱	體系別
class SchoolList {
    // typedef struct sT {
    //     string  sname ;         // school name
    //     string  dname ;         // department name
    //     string  type ;          // either day or night
    //     string  level ;         // graduate or undergraduate
    //     int     nstud ;         // number of students
    //     int     nprof ;         // number of professors
    //     int     ngrad ;         // number of graduates
    // } schoolType ;              // structure of school data

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

//**************mission 1 *************//

struct heapNode{
	int place ;
	int gdNum ;
};

class Heap{
	int sizeH = 0 ;
	heapNode *item;
	vector <heapNode> heapSet ; // EX

    public:	
	Heap(){
	}
	~Heap(){
	}
		
	bool heapIsEmpty( ) ; 
	void BuildHeap( vector<schoolType> classSet ) ; 
	int LeftMost( int size ) ;
     
};

void Heap::BuildHeap( vector<schoolType> classSet ) { // �إ�Heap 

    int size = classSet.size() ;
    item = new heapNode[size] ; //�إ�Array 
	for( int i = 0; i < size ; i ++ ){
		// if( sizeH >= size )
		// 	cout << "HeapFull" ;
			
		int place = i ;
		int parent = ( place - 1 ) / 2 ;
		

		item[i].gdNum = classSet[i].ngrad ; //  ���NClassSet����Ʃ�JHeap�̥��� 
		item[i].place = place + 1 ; // �q�@�}�l���Ǹ� 

		
		while( ( parent >= 0 ) && ( item[place].gdNum < item[parent].gdNum ) && (place >= 0)){ // ���s�ƶ��� 

           	int tempGd ;
           	int tempPlace ;
           	
           	tempGd = item[parent].gdNum ;
           	tempPlace = item[parent].place ;
           	
           	item[parent].gdNum = item[place].gdNum ;
           	item[parent].place = item[place].place ;
           	
           	item[place].gdNum = tempGd ;
           	item[place].place = tempPlace ;
            
			place = parent ;
			parent = ( place - 1 )/ 2 ;
		} // while
        
		
	
	} // for
	
	
	
	cout << "<min heap>" << "\n" ; // �}�l�L��� 
	cout << "root:" <<"["<< item[0].place <<"]" ;
	cout << item[0].gdNum << "\n" ; 
	
	cout << "bottom:" << "[" << item[size-1].place << "]" ;
	cout << item[size-1].gdNum << "\n" ; 
	
	cout << "leftmost bottom:[" ; 
	cout << item[LeftMost(size)].place << "]" ;
	cout << item[LeftMost(size)].gdNum << "\n" ;  
	

    /*for( int j = 0 ; j < size ; j++ ){
    	cout << item[j].place << "  " << item[j].gdNum << "\n";
	} // for*/

	
} // BuildHeap

int Heap::LeftMost( int size ) { // ���̥��`�I����m 
	int place = 0 ;
    for ( int i = 1 ; i < size ; i=i*2 ){
    	place = i-1 ;
	} // for
	
	return place ;
} // LeftMost

bool Heap::heapIsEmpty( ) {
	if ( sizeH == 0 ) {
		return true ;
	} // if
	else {
		return false ;
	}
} // heapIsEmpty()

//***********mission 2*********************//

struct HeapType{                            //Heap's node
    int idx, key_ngrad ;                    //store index & number of students
    HeapType():idx(0),key_ngrad(0){} ;
    HeapType( int num, int key ):idx(num), key_ngrad(key){} ;
};

class MinMaxHeap{                           //MinMaxHeap
private:
    std::vector<HeapType> minmaxheap;                           //store Matrix of HeapType data
    void swap ( struct HeapType &p1, struct HeapType &p2 );        //swap node
    int GetParent( int num ){ return num/2 ; };
    int GetGrendParent( int num ){ return num/4 ; };
public:
    MinMaxHeap(){                       // default constructor will reserve heap[0]
        minmaxheap.resize( 1 );         // if HeapType is added later, it will be added from heap[1]
    }
    MinMaxHeap(int n){
        minmaxheap.resize( n + 1 ) ;
    }
    bool IsHeapEmpty(){ return ( minmaxheap.size()<1) ; } ;

    bool MinorMaxlevel( int node ) ;
    void BuildMinMaxHeap(std::vector<schoolType> array) ;
    void MinHeapfy(int node) ;
    void MaxHeapfy(int node) ;
    
};
//***************************************//
//*****************msg*******************//
//***************************************//
void MinMaxHeap::swap ( struct HeapType &p1, struct HeapType &p2 ){        //swap node
	
	struct HeapType temp = p1;
    p1 = p2;
    p2 = temp;

} // end swap

bool MinMaxHeap::MinorMaxlevel(int node){
    // min = true, max = false 
    int doublenum = 1 ;         // 2,4,8,16,32,64...
    bool text = false ;
    do {
        if ( text ) {   //0,2,4,8.... / 2, remainder = 0 
            text = false ;      // max = false
        } // if
        else
        {                       //1,3,5,7.... / 2, remainder = 1
            text = true ;       // min = true
        } // else

        doublenum = doublenum * 2 ;
        
    } while ( doublenum <= node ) ;

    return text ;
} // end MinorMaxlevel

void MinMaxHeap::MinHeapfy(int node) {

    if ( node > 3 && minmaxheap[node].key_ngrad < minmaxheap[ GetGrendParent(node) ].key_ngrad ) {   // node 1, 2, 3 don't has grandparent
        //min and grandmin level naod compare
        swap(minmaxheap[node],minmaxheap[ GetGrendParent(node) ]) ;
        MinHeapfy( GetGrendParent(node) ) ;
    } //end if

} // end MinHeapfy

void MinMaxHeap::MaxHeapfy(int node) {

    if ( node > 3 && minmaxheap[node].key_ngrad > minmaxheap[ GetGrendParent(node) ].key_ngrad ) {   // node 1, 2, 3 don't has grandparent
        //max and grandmax level naod compare
        swap(minmaxheap[node],minmaxheap[ GetGrendParent(node) ]) ;
        MaxHeapfy( GetGrendParent(node) ) ;
    } //end if

} // end MinHeapfy

void MinMaxHeap::BuildMinMaxHeap(std::vector<schoolType> array){

    // Put the data of array[] into the matrix of heap, and reserve heap[0] not to use
    for (int i = 0; i < array.size(); i++) {     
        
        minmaxheap[i + 1].idx = i + 1;                          // Treat the idx of array[] as an element
        minmaxheap[i + 1].key_ngrad = array[i].ngrad;       // Treat the value of array[] as the key
        
        //cout << minmaxheap[i+1].idx << " " << minmaxheap[i+1].key_ngrad << " " << i + 1 << endl ;
        //1. decide which level min or max
        //2. check whether to swap with its parent
        
        if ( i + 1 == 1 ) {
            //nothing, data store into vextor

        } // end if
        else if ( i + 1 >= 2 && i + 1 <= 3 ) {
            
            if ( minmaxheap[i + 1].key_ngrad < minmaxheap[ GetParent( i + 1 ) ].key_ngrad )    // insert node > it's perant node
                swap(minmaxheap[ i + 1],minmaxheap[ GetParent( i + 1 ) ]) ;

        } // end else if
        else if ( i + 1 >= 4 && i + 1 <= 7 ) {

            if ( minmaxheap[i + 1].key_ngrad > minmaxheap[ GetParent( i + 1 ) ].key_ngrad ){    // insert node < it's perant node
                    swap(minmaxheap[ i + 1],minmaxheap[ GetParent( i + 1 ) ]) ;                 //swap
                    
                } //end if
            else 
                MinHeapfy( i + 1 ) ;         //with it grand node compare

        } // end else if
        else {

            if ( MinorMaxlevel(i + 1) ) {   //node in min Level
                
                if ( minmaxheap[i + 1].key_ngrad > minmaxheap[ GetParent( i + 1 ) ].key_ngrad ){    // insert node > it's perant node
                    swap(minmaxheap[ i + 1],minmaxheap[ GetParent( i + 1 ) ]) ;                     //swap
                    MaxHeapfy( GetParent( i + 1 ) ) ;         //with it grand node compare
                    
                } //end if  
                else 
                    MinHeapfy( i + 1 ) ;         //with it grand node compare

            } // end if
            else {                          //node in max level

                if ( minmaxheap[i + 1].key_ngrad < minmaxheap[ GetParent( i + 1 ) ].key_ngrad ){    // insert node > it's perant node
                    swap(minmaxheap[ i + 1],minmaxheap[ GetParent( i + 1 ) ]) ;                     //swap
                    MinHeapfy( GetParent( i + 1 ) ) ;         //with it grand node compare
                    
                } //end if  
                else 
                    MaxHeapfy( i + 1 ) ;         //with it grand node compare

            } // end else

        } // end else

    } // end for
    
    //*****print data***********//

  	int doublenum = 1 ;         // 2,4,8,16,32,64...
	int LeftCornerNum = 1 ;
	
	do {
         doublenum = doublenum * 2 ;
         LeftCornerNum = doublenum/2 ;
    } while ( doublenum < array.size() ) ;

	cout << "Root: [" << minmaxheap[1].idx << "], (" << minmaxheap[1].key_ngrad << ") " << endl ;
	cout << "Bottom: [" << minmaxheap[array.size()].idx << "], (" << minmaxheap[array.size()].key_ngrad << ") " << endl ;
	cout << "Leftmost Bottom: [" << minmaxheap[LeftCornerNum].idx << "], (" << minmaxheap[LeftCornerNum].key_ngrad << ") " << endl ;

    // cout << MinorMaxlevel(1) << " " << MinorMaxlevel(2) << " " << MinorMaxlevel(3) << " " << MinorMaxlevel(4) << " " << MinorMaxlevel(7) << " " << MinorMaxlevel(8) << endl ;
    // cout << true << false << endl ;

} // end BuildMinMaxHeap

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

    Heap Mission1 ;         // mission 1

    SchoolList ListR ;          //call the list
    MinMaxHeap Misson2 ;
    
    string orderkey = "" ;      //contral mission (1,2,end)
    bool text = true ;          //contral Loop

    while ( text ) {
        if (ListR.readFile()) {     //read the data
            //ListR.printFile() ;   //see if bug exist
            msg1();
            cin >> orderkey ;            
            if ( orderkey == "1" ) {            // mission 1
                Mission1.BuildHeap( ListR.getFile() ) ; //  Heap 
            } // end if
            else if ( orderkey == "2" ) {       // mission 2
				Misson2.BuildMinMaxHeap(ListR.getFile()) ;
            } // end elseif
            else { msg2(); text = false ; }     //end the Loop
        
        } // end if
	
    } // end while
    
		
    system("pause");
    return 0 ;
}
