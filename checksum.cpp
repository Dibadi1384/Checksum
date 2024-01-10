#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif


//write funcytions here

// add_checksum: adds a checksum to a single piece of data
unsigned int add_checksum( unsigned int n ){
	if (std::to_string(n).size()<9){
		int sum=0;
		unsigned int ninitial=n;
		int x;
   		bool j=true;
		while(n>=1){
			if (j){
				x=(n%10)*2;
				j=false;
			}
			else{
				x=(n%10);
				j=true;
			}
			n=int(n/10);
			if (x<9){
				sum+=x;
			}
			else{
				for(int i=0; i<1; i++){
				int y=x%10;
				int z=int(x/10);
				sum=sum+y+z;
				}  
			}
		}
		int d=(sum*9)%10;
		std::string nfinalstr=std::to_string(ninitial)+std::to_string(d);
		unsigned int nfinal=stoi(nfinalstr);
		return nfinal;
   }
   
   else{
		unsigned int error={4294967295};
		return error;
   }
}

// add_checksum: adds checksums for each piece of data in a list
void add_checksum( unsigned int array[], std::size_t capacity ){
	for(int k(0); k<capacity; k++){
		array[k]=add_checksum(array[k]);
	} 
}

// verify_checksum: returns true if data is a valid checksum
bool verify_checksum( unsigned int n ){
	unsigned int nwod=int(n/10);
	if(std::to_string(n).size()<10){
		if(add_checksum(nwod)==n){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

// remove_checksum: removes checksums from valid data
// otherwise returns error code
unsigned int remove_checksum( unsigned int n ){
if(verify_checksum(n)==true){
	std::string nstr=std::to_string(n);
	unsigned int nrd=stoi(nstr.substr(0,nstr.size()-1));
	return nrd;
}
else{
	unsigned int nrd={4294967295};
	return nrd;
}
}


// remove_checksum: removes/errors checksums for each piece of data in a list
void remove_checksum( unsigned int array[], std::size_t capacity ){
	for(int k(0); k<capacity; k++){
		array[k]=remove_checksum(array[k]);
	} 
}

//Testing 
#ifndef MARMOSET_TESTING
int main() {
	unsigned int value_to_protect{21352411};
	unsigned int protected_value = add_checksum(value_to_protect);
	std::cout << "The value " << value_to_protect
		<< " with the checksum added is " << protected_value
		<< "." << std::endl;
	
	if (verify_checksum(protected_value))
	{
		std::cout << "The checksum is valid." << std::endl;
	}
	else   {
		std::cout << "The checksum is invalid." << std::endl;
	} 
	const std::size_t QTY_VALUES {3};
	unsigned int value_series[QTY_VALUES] {20201122, 20209913, 20224012};
	
	add_checksum(value_series, QTY_VALUES);
	
	std::cout << "Series with checksums added: ";
	for (std::size_t series_index {0};
		series_index < QTY_VALUES; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}

    std::cout << std::endl;
    return 0;
}
#endif