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
	int hValue ;
} StudentType;


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
//*********************************8*******************************

class List{
	
	vector<StudentType> studentSetZ ;
	/*vector<StudentTypeH> studentSet ;*/
	string fileNum ;
	
	public:
		
	    List(){
		
	    }
	    ~List(){
		
	    }
	
	bool readBinary(string fileName){
		fstream binFile ;
		StudentType oneSt ;
		int stNo = 0 ;
		fileName = "input" + fileName + ".bin" ;
		
		binFile.open(fileName.c_str(), fstream::in | fstream::binary );
		if( binFile.is_open()){
			binFile.seekg(0, binFile.end) ;
			stNo = binFile.tellg()/sizeof(oneSt) ;
			binFile.seekg(0, binFile.beg) ;
			for(int i = 0; i < stNo; i++ ){
				binFile.read((char*)&oneSt, sizeof(oneSt));
				studentSetZ.push_back(oneSt);
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

	
	vector<StudentType> GetSet(){
		return studentSetZ ;
	} // GetSet
	

	
};


//************************************************************************************

class HashList{
	
	int hashSize ; // 之後方便建array 
	int detaSize ; // 共有多少資料 
	float nonExistNum ; // 不存在值 
	float existNum ; // 現存值 
	StudentType *hashList ;
	

	
	public:
		
	HashList(){
		hashSize = 0 ;
		detaSize = 0 ;
		nonExistNum = 0.0 ;
		existNum = 0.0 ;
	}
	
	~HashList(){
		
	}
	
	bool IsPrime( int num ){ // Check if the num is a prime
		if( num == 1 ){
			return false ;
		} // if
		else{
			for( int i = 1; i < num; i++ ){
				if( num%i == 0 ){
					return false ;
				} // if
			} // for
		} // else
		
		return true ;
		
	} // IsPrime
		
	bool BuildTable(){ // if there's a .bin file, return true 
	    List alist ;
	    string fileName ;
	    cout << "Enter Bin fileName : \n" ;
	    cin >> fileName ;
	    
	    
	    
	    if( alist.readBinary(fileName) ){
	    	
	    	hashSize = alist.GetSet().size() ; // Build the array based on hashSize( bigger than 1.2 & is prime ) 
	    	detaSize = hashSize ;
	    	hashSize = hashSize * 13 ;
	    	hashSize = hashSize / 10 ;
	    	//cout << hashSize << "\n" ;
	    	
	    	
	    	while( IsPrime( hashSize ) ){
	    		hashSize++ ;
			} // while

            cout << hashSize << "\n" ;
	    	hashList = new StudentType[hashSize] ;
	    	
	    	for( int i = 0 ; i < alist.GetSet().size() ; i++ ){ // Insert the deta one by one
	    		HashInsert( alist.GetSet()[i], hashList ) ;
			} // for
			
			// cout << nonExistNum << " " << existNum << "\n";
			PrintOutFile(fileName) ;
			Print() ;
			return true ;
	    	
		} // if
		else{
			return false ; // Build Table failed.
		} // else
		
	} // BulidList

	
	void HashInsert( StudentType aStudent, StudentType* hashList ){ // Hash Insert
	    //cout << aStudent.sid << "\n" ;
	    
		aStudent.hValue = InvertToKey( aStudent.sid ) ; // Set hValue
		// cout << aStudent.hValue << "\n" ;
		
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
	
	int InvertToKey( char sid[10] ){ // Change student id into the key value we want
		int keynum = 1; 
		int temp = 0;
		
		for( int i = 0; i < 10 ; i++ ){ // that temp equals to the value of sid's char, and mutiply by keynum
			temp = sid[0] - '0' ;
		    keynum = keynum * temp ;
		} // for
		
		return keynum ;
	} // InvertToKey

	
	bool SpotEmpty( int spot, StudentType* hashList ){ // Find Out is that spot empty
		if( hashList[spot].hValue == 0 ){
			return false ;
		} // if
		else{
			return true ;
		} // else
	} // SpotEmpty
		

    void PrintOutFile( string fileName ){
    	fstream  outFile ;
    	fileName = "linear" + fileName + ".txt" ;
    	outFile.open(fileName.c_str(), ios::out | ios::trunc);
    	
    	for( int j = 0 ; j < hashSize ; j++ ){
    		outFile.write(hashList[j].sid, 10) ;
    		outFile.write(hashList[j].sname, 10) ;
    		
    		
		} // wfor
    	
    	outFile.write(hashList[0].sid, 10) ;
    	
	} // Print
	
	void Print(){
		float numNE = 0.0 ;
        float numE = 0.0 ;
        float detaSizef = (float) detaSize ;
        float hashSizef = (float) hashSize ;
        
        numNE = nonExistNum / hashSizef ;
        numE = existNum / detaSizef ;
        
        cout << "unsuccessful search: "<< setprecision(4) << numNE << " comparisons on averge\n" ;
        cout << "successful search: "<< setprecision(4) << numE << " comparisons on averge\n" ;
        
        
	} //Print
		
};

//**********************************************************************************

int main(){
	int cmd ;
	string fileName ;
	HashList hList;
	
	bool haveBin = false ;
	cout << "Enter CMD:(0)Quit (1)Text to Binary (2)Linear Search \n" ;
	cin >> cmd ;
	while( cmd != 0 ){
	
		if( cmd == 1 ){
            TextToBinary(fileName) ;
            haveBin = true ;
		} // if
		else if( cmd == 2 ){
			if( hList.BuildTable() ){
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





























