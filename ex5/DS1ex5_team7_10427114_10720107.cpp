// 10720107 ���A�� 10427114 ���[�@ �ЧU�ФU��Github��������

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
		
		} // readFileByP
		
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
			cout << "adjL.size: "<<adjL.size()<<"\n" ;
			
			int ans = BinarySearch(0, adjL.size()-1 , strId ); // Start to find
			
			return ans ;
		} // Locate
				
		int BinarySearch( int first, int last, string strId ){ // return the position of the thing we're looking for, if nothing, return -1
            int num = last - first ;
			if( num >= 0 ){
				
				
				int mid =  first + ( last - first ) / 2 ;
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
			else{
				return -1 ;
			} // else	
			
		} // BinarySearch
		
		int Search( string strid ){
			int ans = -1 ;
			
			for( int i = 0; i < adjL.size(); i++ ){
				if( strcmp(strid.c_str(), adjL[i].sid1.c_str()) == 0 ){
					ans = i ;
				} // if
			} // for
			
			return ans ;
			
		} // Search

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
		
		void BSort(){
			for( int i = 0; i < adjL.size(); i++ ){
				for( int j = i ; j < adjL.size() ; j++ ){
					if( strcmp(adjL[j].sid1.c_str(), adjL[i].sid1.c_str() ) < 0 ){
						string temp = adjL[i].sid1 ;
						adjL[i].sid1 = adjL[j].sid1 ;
						adjL[j].sid1 = temp ;
					} // if
				} // for
			} // for
		} //BSort()
		
		void InsertNode( adjListNode* &head, adjListNode* &aNode ){
			
			bool insert = false ;
			
			if( head == NULL ){
				head = aNode ;
			} // if
			else if( head->next == NULL ){
				if( strcmp(head->sid2.c_str(), aNode->sid2.c_str()) > 0 ){ 
				    aNode->next = head ;
					head = aNode ;
				} // if
				else{
					head->next = aNode ;
				} // else
			} // else if
			else{
                if( strcmp(head->next->sid2.c_str(), aNode->sid2.c_str()) > 0 ){
                    aNode->next = head->next ;
                    head = aNode ;
				} // if
				else{
					InsertNode( head->next, aNode ) ;
				} // else
			} // else

		} // InsertNode
	    
	    string charToString( char array[10] ){
	    	string ans = "" ;
	    	for( int i = 0 ; i < 10 ; i++ ){
	    		ans = ans + array[i] ;
			} // for
			
			return ans ;
		} // charToString
		
			
	    bool Create( string fileName ){ // read pairs from a file into adjacency list
	        vector<StudentPair> sList ;
	        adjList aAdj ;
	        aAdj.head = NULL ;
	        
	        adjListNode* aNode = new adjListNode ;
	        aNode->next = NULL ;
	        
	        if( ReadFileByP(sList, fileName ) ){
	        	
	        	//cout << "size:" << sList.size() << "\n";
	        	
	        	for( int i = 0 ; i < sList.size() ; i++ ){ //PushBack all deta into adjL
	        	    //1. save sender&receiver
	        	    aAdj.sid1 = charToString( sList[i].sid1 ) ; // sender
	                aNode->sid2 = charToString( sList[i].sid2 ) ; // reciever
	                aNode->weight = sList[i].wgt ;
	                aNode->next == NULL ;
	                
	                //cout << "sid1:"<< aAdj.sid1 << "\n" ;
	                //cout << "sid2:"<< aNode->sid2 << "\n" ;
	                
	                int spot1 = Search(aAdj.sid1) ;
	                int spot2 = Search(aNode->sid2) ;
	                cout << "Spot1:" << spot1 << "\n";
	                cout << "Spot2:" << spot2 << "\n";
	                
	                if( spot2 == -1 ){ // if receiver's id heven't show up in the list yet
	                    adjList bAdj ;
						bAdj.sid1 = aNode->sid2 ;
						bAdj.head = NULL ;
						adjL.push_back(bAdj) ;	
					} // if
					
					
					if( spot1 == -1 ){ // if this is new on the list
					   
					    
						InsertNode( aAdj.head, aNode ) ;
						
						//cout << "hi" ;
						adjL.push_back(aAdj) ;
					} // if
					else{ // if it isn't new on the list
					    
					    InsertNode( adjL[spot1].head, aNode ) ;
					} // else
					
					
					
				} // for
				
                BSort() ;
	        	
	        	return true ;
			} // if
			else{
				return false ;
			} // else
	    
		} // Create
	    void SaveF( string fileName ) ; // write adjacency lists as a file
	    
	    /*void clearUp(){
	    	clearUp(adjL);
		} // ClearUp*/
		
		~Graph(){
			
		} // destructor
	
};





void Graph::SaveF( string fileName ){
	fstream  outFile ;
    fileName = "pairs" + fileName + ".adj" ;
    outFile.open(fileName.c_str(), ios::out | ios::trunc);
    
    
    cout << adjL.size() ;
    
    for( int i = 0 ; i < adjL.size() ; i++ ){
    	outFile << "[" << i+1 << "]" ;
    	outFile << ":" << adjL[i].sid1 << "\n" ;
    	
    	
	} // ofr
    
    
} // SaveF()
