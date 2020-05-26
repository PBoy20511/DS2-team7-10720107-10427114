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
	// float wgtLB; // lower bound of weights
	
	
	bool ReadFile( vector<StudentPair> &fileList ) ; // get all records from a file
	void Insert( adjList &aAdj ); // insert an adj list
	int Locate( vector<adjList> &list, string &key ) ; // locate the index in adj List
	int Locate( string key ) {
		return locate( adjL, key ) ;
	} // Locate
	
	bool AddCount( adjListNode*nodeOne, adjListNode*nodeTwo ) ; // count only if not visited yet
	void SavelNF( vector<adjList> &list, string key ) ; // write influence values as a file
	void ClearUp( vector<adjList> &list ) ; // release the space of adjancency lists
	
	public:
		Graph(): fileNO(""), wgtLB(0){
		} // default constructor
		
		Graph(Graph &obj): adjL( obj.adjL), fileNO(onj.fileNO), wgtLB(0){
		} // shallow copy constructor
		
		bool Existed(){
			return adjL.size();
		} // Exsited
		
		/*void SetLB( float v ){ // set up the velue of wgtLB
			wgtLB = v ;
		} // SetLB */
	    adjList *FoundNode( string strId ){ // Use Binary Search to find the node we're lookinf for

	    	int ans = BinarySearch( 0, adjL.size(), strId ) ; // Start to find
	    	
	    	if( ans = -1 ){
	    		return NULL ;
			} // if
			else{
				return adjL[ans] ;
			} // else
	    	
		} // HaveAppear
		
		int BinarySearch( int first, int size, string strId ){ // return the position of the thing we're looking for, if nothing, return -1

			if( size > 0 ){
				
				int mid = first + (last - 1) / 2 ;
				if( strcmp( strId, adjL[mid] ) == 0 ){ // Find the one
					return mid ;
				} // if
				else if( strcmp( strId, adjL[mid] ) < 0 ){
					return BinarySearch( first, mid-1, strId );
				} // else if
				else{
					return BinarySearch( mid+1, size, strId ) ;
				} // else
				
			} // if
			
			return -1 ;
			
			
		} // BinarySearch
		
        int BinaryInsert( int first, int size, string sid1 ){
        	if( strcmp( strId, adjL[0]) < 0 ){
        		return -2 ;
			} // if
			else{
				if( size >= 0 ){
				
					int mid = (first + size) / 2 ;
				
					if( strcmp( strId, adjL[mid] ) < 0 && strcmp( strId, adjL[mid-1] ) > 0 ){ // Find the one
						return mid ;
					} // if
					else if( strcmp( strId, adjL[mid] ) < 0 ){
						return BinarySearch( first, mid-1, strId );
					} // else if
				    else{
				    	return BinarySearch( mid+1, size, strId ) ;
			    	} // else
				
		    	} // if
			
	    		return -1 ;
			} // else
			
			
		} // BinaryInsert
		
		void InsertALN( adjListNode temp ){
			
		} // InsertALN
		
		
	    bool Create(); // read pairs from a file into adjacency list
	    void SaveF() ; // write adjacency lists as a file
	    
	    // void compINF( string tempStr ); // compute influnce values by BFS
	    // void compINF() ; // compute influnce values by DFS
	    
	    void clearUp(){
	    	clearUp(adjL);
		} // ClearUp
		
		~Graph(){
			clearUp() ;
		} // destructor
	
};

bool Graph::Create(){
	vector<StudentPair> fileList ;
	adjList aAdj ;
	
	if( ReadFile( fileList ) ){
        for( int i = 0 ; i < fileList.size() ; i++ ){
        	strcpy( aAdj.sid.c_str() ,fileList[i].sid1 ) ; // save sender
        	
        	adjListNode temp ;
        	strcpy(temp.sid2.c_str(), fileList[i].sid2 ) ; // save receiver
        	temp.weight = fileList[i].wgt ;
        	
            adjListNode *walk = FoundNode( fileList[i].sid1 ) ; // Check whether if the node were already in the list or not
            if( walk == NULL ){ // if the node does not exist
            	Insert( aAdj ) ;
			} // if
			else{ // the node does exist

			} // else
            
		} // for
	} // if
	else{
		cout << "No Such File!" ;
	} // else
	
} // Creat()


void Graph::Insert( adjList &aAdj ) { // Insert the node to the right place
    int ans = BinaryInsert( 0, adjL.size()-1, aAdj.sid1 ) ;
    
    if( ans = -1 ){ //  the last one
    	adjL.push_back( aAdj ) ;
	} // if
	else if( ans == -2 ){ // the first one
		adjL.insert( 0, aAdj ) ;
	} // else if
	else{
		adjL.insert( ans, aAdj ) ;
	} // else
	
} // Insert()

















