// 10720107 陳丕中 10427114 熊觀一 請助教下載Github版本評分

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<queue>
#include<stack>
#include<algorithm>

using namespace std ;



class Graph{
	
	typedef struct sP{ // student pair
		char sid1[10] ; // 1st sid: sender
		char sid2[10] ; // 2nd sid: receiver
		float wgt ; // pair weight
	}StudentPair;
	
	typedef struct aLN{ // node of adjacency lists
		string sid2; // receiver
		float weight ; // pair weight
		struct aLN *next; // pointer to the next Node
	} adjListNode;
	
	typedef struct aL{ // adjacency list
		string sid1 ; // sender
		adjListNode *head; // pointer to the first node of a list
		int inf ; // influence value
	}adjList;
	
	vector<adjList> adjL; // the adjacency lists
	string fileNO ; // a number to form a file name
	float wgtLB; // lower bound of weights
	
	
	bool ReadFile( vector<StudentPair> &fileList ) ; // get all records from a file
	void Insert( adjList &aAdj ); // insert an adj list
	
	//int Locate( vector<adjList> &list, string &key ) ; // locate the index in adj List
	//int Locate( string key ) {
	//	return locate( adjL, key ) ;
	//} // Locate
	
	bool AddCount( adjListNode*nodeOne, adjListNode*nodeTwo ) ; // count only if not visited yet
	void SavelNF( vector<adjList> &list, string key ) ; // write influence values as a file
	void ClearUp( vector<adjList> &list ) ; // release the space of adjancency lists
	
	public:
		Graph(): fileNO(""), wgtLB(0){
		} // default constructor
		
		Graph(Graph &obj): adjL( obj.adjL), fileNO(obj.fileNO), wgtLB(0){
		} // shallow copy constructor
		
		bool Existed(){
			return adjL.size();
		} // Exsited
		
		/*void SetLB( float v ){ // set up the velue of wgtLB
			wgtLB = v ;
		} // SetLB */
		
		bool ReadFileByP( vector<StudentPair> &fileList, string fileName ){ // ReadFile() made By Peter heheh
			fstream binFile ;
			StudentPair oneSt ;
			int stNo = 0 ;
			fileName = "pairs" + fileName + ".bin" ;
		
			binFile.open(fileName.c_str(), fstream::in | fstream::binary );
			if( binFile.is_open()){
				binFile.seekg(0, binFile.end) ;
				stNo = binFile.tellg()/sizeof(oneSt) ;
				binFile.seekg(0, binFile.beg) ;
				for(int i = 0; i < stNo; i++ ){
					binFile.read((char*)&oneSt, sizeof(oneSt));
					fileList.push_back(oneSt);
					// cout << "[" << i+1 << "]" << studentSetZ[i].sid << "," << oneSt.sname << endl ;
				} // for
				
			    binFile.close() ;
			    return true ;
			} // if
			else{
				binFile.close();
				return false ;
			} // else
		
		} // readBinary
		
	    /*aL *FoundNode( string strId ){ // Use Binary Search to find the node we're lookinf for

	    	int ans = BinarySearch( 0, adjL.size(), strId ) ; // Start to find
	    	
	    	if( ans = -1 ){
	    		return NULL ;
			} // if
			else{
				adjList *temp ;
				temp = adjL[ans] ;
				return temp ;
			} // else
	    	
		} // FoundNode()*/
		
		int Locate( string strId ){
			int ans = BinarySearch(0, adjL.size()-1 , strId.c_str( )) ; // Start to find
			
			return ans ;
		} // Locate
				
		int BinarySearch( int first, int last, string strId ){ // return the position of the thing we're looking for, if nothing, return -1

			if( last > 0 ){
				
				int mid = first + (last - 1) / 2 ;
				if( strcmp( strId.c_str(), adjL[mid].sid1.c_str() ) == 0 ){ // Find the one
					return mid ;
				} // if
				else if( strcmp( strId.c_str(), adjL[mid].sid1.c_str() ) < 0 ){
					return BinarySearch( first, mid-1, strId );
				} // else if
				else{
					return BinarySearch( mid+1, last, strId ) ;
				} // else
				
			} // if
			
			return -1 ;
			
			
		} // BinarySearch
		
        int BinaryInsert( int first, int size, string strId ){
        	if( strcmp( strId.c_str(), adjL[0].sid1.c_str()) < 0 ){
        		return -2 ;
			} // if
			else{
				if( size >= 0 ){
				
					int mid = (first + size) / 2 ;
				
					if( strcmp( strId.c_str(), adjL[mid].sid1.c_str() ) < 0 && strcmp( strId.c_str(), adjL[mid-1].sid1.c_str() ) > 0 ){ // Find the one
						return mid ;
					} // if
					else if( strcmp( strId.c_str(), adjL[mid].sid1.c_str() ) < 0 ){
						return BinarySearch( first, mid-1, strId );
					} // else if
				    else{
				    	return BinarySearch( mid+1, size, strId ) ;
			    	} // else
				
		    	} // if
			
	    		return -1 ;
			} // else
			
			
		} // BinaryInsert
		
		void InsertALN( int spot, adjListNode *&node ){ // Insert an adjListNode into an adjList
        // if i wanna rise up the speed, i should use binary search
        
    
			bool insert = false ;
			adjListNode *walk ;
			do{	// find the spot i wanna insert
				adjL[spot].head = walk ;
				if( walk->next->sid2 < node->sid2 && walk->sid2 > node->sid2 ){
					insert = true ;
				} // if		
			} while( !insert && walk->next != NULL );
			
			if( insert ){ // if the node isn't the last one
				node->next = walk->next ;
				walk->next = node ;
			} // if
			else{ // if it is the last node on the list
				walk->next = node ;
				node->next = NULL ;
			} // else
			
		} // InsertALN
		
	
	
	    // void compINF( string tempStr ); // compute influnce values by BFS
	    // void compINF() ; // compute influnce values by DFS
		
			
	    bool Create( string fileName); // read pairs from a file into adjacency list
	    void SaveF( string fileName ) ; // write adjacency lists as a file
	    
	    /*void clearUp(){
	    	clearUp(adjL);
		} // ClearUp*/
		
		~Graph(){
			
		} // destructor
	
};

bool Graph::Create( string fileName ){
	vector<StudentPair> fileList ; // all the file's record
	adjList aAdj ;	
	
	if( ReadFileByP( fileList, fileName ) ){
        for( int i = 0 ; i < fileList.size() ; i++ ){
        	aAdj.sid1 = fileList[i].sid1 ; // save sender
        	
        	adjListNode *temp = new adjListNode ;
        	temp->sid2 = fileList[i].sid2 ; // save receiver
        	temp->weight = fileList[i].wgt ;
        	
            int spot = Locate(aAdj.sid1) ;// Check whether if the node were already in the list or not
            if( spot == -1 ){ // if the node does not exist
            	Insert( aAdj ) ; // push_back the aAdj into the vector
			} // if
			else{ // the node does exist
                InsertALN( spot, temp ) ; // Insert temp into the right spot
			} // else
            
		} // for
		
		return true ;
	} // if
	else{
		return false ;
	} // else
	
} // Creat()


void Graph::Insert( adjList &aAdj ) { // Insert the node to the right place

    
    int ans = BinaryInsert( 0, adjL.size()-1, aAdj.sid1 ) ;
    
    if( ans = -1 ){ //  the last one
    	adjL.push_back( aAdj ) ;
	} // if
	else if( ans == -2 ){ // the first one
		adjL.insert( adjL.begin(), aAdj ) ;
	} // else if
	else{
		ans = ans + 1 ;
		adjL.insert( adjL.begin()+ans, aAdj ) ;
		
	} // else
	
} // Insert()

void Graph::SaveF( string fileName ){
	fstream  outFile ;
    fileName = "pairs" + fileName + ".adj" ;
    outFile.open(fileName.c_str(), ios::out | ios::trunc);
    
    outFile << "Hello world!" ;
    
} // SaveF()




int main(){
	int cmd ;
	string fileName ;
	Graph graph;
	
	bool haveBin = false ;
	cout << "Enter CMD:(0)Quit (1)Mission One " ;
	cin >> cmd ;
	while( cmd != 0 ){
	
		if( cmd == 1 ){
            cout << "Enter your file name!" ;
            cin >> fileName ;
            if( graph.Create(fileName) ){
            	graph.SaveF( fileName ) ;
			} // if
			else{
				cout << "No Such File!" ;
			} // else
		} // if
        else{
        	cout << "No Such Cmd!" ;
		} // else
		
		cout << "Enter CMD:(0)Quit (1)Quit (2)Mission One \n" ;
		cin >> cmd ;
		
    } // while
} // main()












