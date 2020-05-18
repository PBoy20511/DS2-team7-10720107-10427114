// 10720107 陳丕中 10427114 熊觀一  請助教下載GitHub版本評分

#include<iostream> 
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<iomanip>
#include<fstream>

using namespace std ;

typedef struct ST{
	char sid[10] ; // student id
	char sname[10] ; // student name
	unsigned char score[6] ; 
	float mean ;
} StudentType;


int TextToBinary(string fileName){
	fstream inFile, outFile;
	int stNo = 0 ;
	do{
		cout << "Input a file number:" ;
		cin >> fileName ;
		
		
		if( !fileName.compare("0") ){
			return false ;
		} // if*/
		
        
        inFile.open( ("input"+fileName+".txt").c_str(), fstream::in ); // open a file
        
        if( inFile.is_open() ){
        	break;
		} // if
		
	}while(true);
	
	fileName = "input" + fileName + ".bin" ;
	outFile.open(fileName.c_str(), fstream::out | fstream::binary );
	
	if( outFile.is_open()){
		char rBuf[255] ;
		while( inFile.getline(rBuf, 255, '\n')){
			string temp ;
			StudentType oneSt;
			int cNo = 0, pre = 0, pos = 0;
			
			stNo ++ ;
			temp.assign(rBuf) ;pos = temp.find_first_of('\t', pre );
			
			while( pos != string::npos ){
		        switch(++cNo){
		        	case 1: strcpy(oneSt.sid, temp.substr(pre, pos-pre).c_str());
		        	    break;
		        	case 2: strcpy(oneSt.sname, temp.substr(pre, pos-pre).c_str());
		        	    break;
		        	default: oneSt.score[cNo-3] = atoi(temp.substr(pre, pos-pre).c_str());
		        	    break ;
				} // switch
				
				pre = ++pos ;
				pos = temp.find_first_of('\t', pre );
			} // while
			
			pos = temp.find_last_of('\t') ;
			oneSt.mean = atof(temp.substr(pos+1).c_str());
			outFile.write((char*)&oneSt, sizeof(oneSt));
		} // while
		
		outFile.close();
	} // if
	
	inFile.close();
	return stNo;
}

typedef struct STH{ // StudentType Hash
	char sid[10] ;
	string content ;
	int hValue ;
}StudentTypeH;

typedef struct STHZ{ // Ver.2 of StudentType Hash
	int hValue ;
	string sid ;
	string sname ;
	string score ;
	string mean ;
}StudentTypeHZ;



//*********************************8*******************************

class List{
	
	vector<StudentTypeHZ> studentSetZ ;
	/*vector<StudentTypeH> studentSet ;*/
	string fileNum ;
	
	public:
		
	    List(){
		
	    }
	    ~List(){
		
	    }
	
	

	
	
	vector<StudentTypeHZ> GetSet(){
		return studentSetZ ;
	} // GetSet
	
	bool Load( string fileName ) { 
	// 讀入資料
	 
    	FILE *infile = NULL ;
    	bool success = false ;
    	fileName = "input" + fileName + ".bin" ;
    	infile = fopen(fileName.c_str(), "r" ) ;

		if ( infile == NULL )
			;
		else{

        	char tempChar ;
        	for ( int i = 0 ; i < 3 ; i++ )
        		while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' )
            		;

        	StudentTypeHZ aStudent ; // reset
        	/*aStudent.hValue = 0 ;*/
        	aStudent.sid = "" ;
        	aStudent.sname = "" ;
        	aStudent.score = "" ;
        	aStudent.mean ;
        
			int numTab = 0 ; // Build Temp that will be use later 
			string strid = "" ;
			string strsname = "" ;
			string strscore = "" ;
			string strmean = "" ;
		
        	while ( fscanf( infile, "%c", &tempChar ) != EOF ) { // ReadFile
        	
        		while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' ) { // Read a line
        			if ( tempChar == '\t' )
        				numTab++ ;
        			else if ( numTab == 0 )
        				strid = strid + tempChar ;
        			else if ( numTab == 1 )
        				strsname = strsname + tempChar ;
        			else if ( numTab == 2 )
        				strscore = strscore + tempChar ;
        			else if ( numTab == 8 )
        			    strmean = strmean + tempChar ;
        		
        		} //while
        		
        		aStudent.sid = strid;
        		aStudent.sname = strsname ;
        		aStudent.score = strscore ;
        		aStudent.mean = strmean ;
        	
            	studentSetZ.push_back( aStudent ) ;
            
            	aStudent.sid = "" ;
            	aStudent.sname = "" ;
        	    aStudent.score = "" ;
            	aStudent.mean ;
	        
            	strid = "" ;
            	strscore = "" ;
            	strsname = "" ;
            	strmean = "" ;
            	numTab = 0 ;
            
        	} // while not EOF

        	success = true ;
        	fclose( infile ) ;

		} // else

		return success ;
	} // Load function 1 
	
};



/*bool List::Load( string fileName ) {
    // Load a file, turn it into a vector
    
    fileNum = fileName ;
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

        StudentTypeH aStudent ;
        aStudent.sid = {'0'} ;
        aCollege.content = "" ; // reset
        
		int numTab = 0 ; // what number is up
		string numId = "" ;
		
		while ( fscanf( infile, "%c", &tempChar ) != EOF ) {
			

			while(fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' ){
				for( int i = 0 ; tempChar != '\t' ; i++ ){
			    	aStudent.sid[0] = tempChar ;
			    } // while	
				
				aStudent.content = aStudent.content + tempChar ;		
			} // while
			
			aStudent.sid = atoc( numId.c_str() ) ;
			studentSet.push_back( aStudent ) ;
			
			aStudent.content = 0 ;
			aStudent.sid = 0 ;
		
	    } // while
		

        success = true ;
        fclose( infile ) ;

	} // else

	return success ;

} // Load

*/

//************************************************************************************

class HashList{
	
	int hashSize ;
	int detaSize ;
	float nonExistNum ; // 不存在值 
	float existNum ; // 現存值 
	StudentTypeHZ *hashList ;
	

	
	public:
		
	HashList(){
		hashSize = 0 ;
		detaSize = 0 ;
		nonExistNum = 0.0000 ;
		existNum = 0.0000 ;
	}
	
	~HashList(){
		
	}
	
	bool IsPrime( int num ){ // Check if the num is a prime
		if( num == 1 ){
			return false ;
		} // if
		else{
			for( int i = 0; i < num; i++ ){
				if( num%i == 0 ){
					return false ;
				} // if
			} // for
		} // else
		
		return true ;
		
	} // IsPrime
		
	bool BuildTable(){ // if there's a .bin file, return true 
	    List list ;
	    string fileName ;
	    cout << " Enter Bin fileName : \n" ;
	    cin >> fileName ;
	    
	    if( list.Load(fileName) ){
	    	
	    	hashSize = list.GetSet().size() ; // Build the array based on hashSize( bigger than 1.2 & is prime ) 
	    	detaSize = hashSize ;
	    	hashSize = hashSize * 1.2 ;
	    	while( IsPrime( hashSize ) ){
	    		hashSize++ ;
			} // while
	    	hashList = new StudentTypeHZ[hashSize] ;
	    	
	    	for( int i = 0 ; i < list.GetSet().size() ; i++ ){ // Insert the deta one by one
	    		HashInsert( list.GetSet()[i], hashList ) ;
			} // for
			
			
			Print() ;
			return true ;
	    	
		} // if
		else{
			return false ; // Build Table failed.
		} // else
		
	} // BulidList
	
	int InvertToKey( char sid[10] ){ // Change student id into the key value we want
		int keynum = 0; 
		int temp = 0;
		
		for( int i = 0; i < 10 ; i++ ){ // that temp equals to the value of sid's char, and mutiply by keynum
			temp = sid[0] - '0' ;
		    keynum = keynum * temp ;
		} // for
		
		return keynum ;
	} // InvertToKey
	
	int InvertToKeyZ( string sid ){ // Change student id into the key value we want
        int keyNum = 1;
        char * temp = new char[sid.length()+1] ;
        strcpy(temp, sid.c_str()) ;
        
        int size = sid.length()+1 ;
        
        for( int i = 0 ; i < size ; i++ ){
            keyNum = keyNum * temp[i] ; 	
		
		} // for
		
		return keyNum ;
		
	} // InvertToKey
	
	bool SpotEmpty( int spot, StudentTypeHZ* hashList ){ // Find Out is that spot empty
		if( hashList[spot].hValue == 0 ){
			return false ;
		} // if
		else{
			return true ;
		} // else
	} // SpotEmpty
	
	void HashInsert( StudentTypeHZ aStudent, StudentTypeHZ* hashList ){ // Hash Insert
		aStudent.hValue = InvertToKeyZ( aStudent.sid ) ; // Set hValue
		
		if( aStudent.hValue > hashSize ){ // Set exsiyNum & NonExistNum
			aStudent.hValue = aStudent.hValue % hashSize ;
			nonExistNum++ ;
		} // if
		else{
			existNum ++ ;
		} // else
		
	
		bool insert = false ; // If first Time Insert success, bool = true 
		
		if( SpotEmpty( aStudent.hValue, hashList ) ){ // First Time Insert
			hashList[aStudent.hValue] = aStudent ;
			insert = true ;
		} // if
		
		while( !insert ){ // Not Virgin

			if( SpotEmpty( aStudent.hValue, hashList ) ){
				hashList[aStudent.hValue] = aStudent ;
				insert = true ;
			} // if
		    
		    aStudent.hValue++ ;
		} // while
		
	} // HashInsert
		

    void PrintOutFile(){
    	
	} // Print
	
	void Print(){
		float numNE = 0.0000 ;
        float numE = 0.0000 ;
        float detaSizef = (float) detaSize ;
        float hashSizef = (float) hashSize ;
        
        numNE = nonExistNum / hashSizef ;
        numE = existNum / detaSizef ;
        
        cout << "unsuccessful search: "<< numNE << " comparisons on averge\n" ;
        cout << "successful search: "<< numE << " comparisons on averge\n" ;
        
        
	} //Print
		
};

//**********************************************************************************

int main(){
	int cmd ;
	string fileName ;
	HashList hash ;
	
	bool haveBin = false ;
	cout << "Enter CMD:(0)Quit (1)Text to Binary (2)Linear Search \n" ;
	cin >> cmd ;
	while( cmd != 0 ){
	
		if( cmd == 1 ){
            TextToBinary(fileName) ;
            haveBin = true ;
		} // if
		else if( cmd == 2 ){
			if( hash.BuildTable() ){
			    ;
			} // if
			else{
				cout << "Please build the bin file first!!!" ;
			} // else
			
		} // else if
        else{
        	cout << "No Such Cmd!" ;
		} // else
		
		cout << "Enter CMD:(0)Quit (1)Text to Binary (2)Linear Search \n" ;
		cin >> cmd ;
		
    } // while  
} // main()


















