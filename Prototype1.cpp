#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

#define invalid -1

//This chooses what do you do with votes with same characters twice or three times.
enum Option{
	Invalid = 0,
	Highest = 1,
	Lowest = 2,
};

string invRemover(string s, char last, bool debug);
string remover(string s, char l, Option o, int n, bool debug);
bool dChecker(string s, bool debug);

//removes invalid characters
string invRemover(string s, char last, bool debug=false){
	if(debug){
		cout << s << endl;	//DeBuG
	}
		
	int i=0;
	while(i<s.length()){
		if(s[i]<'A'||last<s[i])	s.erase(i, 1);
		else i++;
	}
	if(debug){
		cout << s << endl;	//DeBuG
	}
		
	return s;
}

//removes double characters depends on option
string remover(string s, char l, Option o, int n, bool debug=false){
	s=invRemover(s, l, debug);
	if(s.empty())	return s;
	
	if(o==Invalid)	return (dChecker(s, debug))?"":s;
	
	bool alS[n] = {false};	//stands for "already seen"
	if(o==Highest){
		//Only the highest one will alive!
		int i=0;
		do{
			//DeBuG Below
			if(debug){
				cout << s << endl;
				for(int j=0; j<i; j++)
					cout << ' ';
				cout << '^' << endl;
			}
			
			if(alS[s[i]-'A']){
				s.erase(i,1);
			}else{
				alS[s[i]-'A']=true;
				i++;
			}
			
			if(debug){
				cout << s << endl;	//DeBuG
			}
				
		}while(i<s.length());
	}else{
		//Only the lowest one will alive!
		int i=s.length()-1;
		do{
			//DeBuG Below
			if(debug){
				cout << s << endl;
			}
				
			for(int j=0; j<i; j++)
				cout << ' ';
			cout << '^' << endl;
			
			if(alS[s[i]-'A']){
				s.erase(i,1);
				i--;
			}else{
				alS[s[i]-'A']=true;
				i--;
			}
			if(debug){
				cout << s << endl;	//DeBuG
			}
				
		}while(i>=0);
	}
	
	return s;
}

//judges if it contains some same characters
bool dChecker(string s, bool debug=false){
	stable_sort(s.begin(), s.end());
	
	if(debug){
		cout << s << endl;	//DeBuG
	}
		
	for(int i=0; i<s.length()-1; i++)
		if(s[i]==s[i+1])	return true;
	return false;
}

int main(int argc, char* argv[]){
	bool debug=false;
	if(argc==2){
		string tmp = argv[1];
		if(tmp=="-d"){
			cout << "Since -d got input, this is running as debug mode.\n";
			debug = true;
		}
	}
	
	cout << "This program is for single voting screen." << endl;
	cout << "How many responses? : ";
	int n;	//how many responses?
	cin >> n;
	if(n<2||n>27){
		//Error
		cout << "That seems too few/many.\n";
	}else{
		int v;	//how many votes to input?
		
		cout << "How many votes? :";
		cin >> v;
		if(v<1){
			cout << "What?! Then this program is inappropriate for that case.\n";
		}else{
			int optnum;
			do{
			cout << "What do you do with votes having same characters twice?\nInput 0 to make them invalid.\nInput 1 to count the highest one.\nInput 2 to count the lowest one.\n :";
			cin >> optnum;
			if(0>optnum&&optnum>2)
				cout << "That's a valid input!\n\n";
			}while(0>optnum&&optnum>2);
			Option option=(Option)optnum;
			
			
			cout << "From now, you must input all the votes. You must separate each vote by space.\n";
			double ms[v][n]={0};	//mini-scores
			unsigned valids = 0;	//how many valid votes?
			
			const char lc = 'A' + n - 1;	//Last character on voting screen.
			//Below Here:gets votes and record placement.
			for(int i=0; i<v; i++){
				string s;
				cin >> s;
				
				//CAPITALIZATION!
				transform(s.begin(), s.end(), s.begin(), ::toupper);
				
				//Removes invalid chars.
				s = remover(s, lc, option, n, debug);
				
				//Here is the new version!
				if(s.empty()){
					//INVALID VOTE!
					cout << "An invalid vote got input.\n";
					for(int j=0; j<n; j++)
						ms[i][j]=invalid;
				}else{
					//VALID VOTE
					valids++;
					const double unranked = (s.length()+1+n)/2.0;
					
					if(debug){
						cout << unranked << endl;	//DeBuG
					}
						
					for(int j=0; j<n; j++){
						int tmp = s.find('A'+j);
						ms[i][j]=(tmp==string::npos)?(n-unranked)*100.0/(n-1.0):(n-tmp-1.0)*100.0/(n-1.0);
					}				
				}
			}
			
			//DeBuG
			if(debug){
				for(int i=0; i<v; i++){
					for(int j=0; j<n; j++)
						//cout << r[i][j] << ' ';
						cout << ms[i][j] << ' ';
					cout << endl;
				}
			}
			
			//Below Here:calculation! hooray!
			if(valids>0){
				//double ravr[n], rsd[n];
				
				//average calculation
				double avr[n], sd[n];
				for(int i=0; i<n; i++){
					double sum=0;
					for(int j=0; j<v; j++){
						//sum+=(r[j][i]==invalid)?0:r[j][i];
						sum+=(ms[j][i]==invalid)?0:ms[j][i];
					}
					avr[i]=sum/valids;
				}
					cout << "Copy and paste the following text to your spreadsheet:\n";
					if(valids>1){
						//ravr[i]=sum/valids;
						
						//SD calculation
						for(int i=0; i<n; i++){
							double sum0=0;
							for(int j=0; j<v; j++){
								sum0+=(ms[j][i]==invalid)?0:pow(ms[j][i]-avr[i], 2);
							}
							sd[i]=sqrt(sum0/valids);
						}
						
						//Below Here:result by character
						cout << "Alphabet\tAverage\tStandard Deviation\n";
						for(int i=0; i<n; i++){
							//cout << (char)('A'+i) << '\t' << ravr[i] << '\t' << rsd[i] << '\n';
							cout << (char)('A'+i) << '\t' << avr[i] << '\t' << sd[i] << '\n';
						}
					}else{
						//Below Here:result by character
						cout << "Alphabet\tAverage\tStandard Deviation\n";
						for(int i=0; i<n; i++){
							//cout << (char)('A'+i) << '\t' << ravr[i] << "\tN/A\n";
							cout << (char)('A'+i) << '\t' << avr[i] << "\tN/A\n";
						}
					}
			}else{
				cout << "There were only invalid votes.... \n";
			}
		}
	}
	return 0;
}

