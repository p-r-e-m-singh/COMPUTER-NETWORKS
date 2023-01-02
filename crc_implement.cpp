#include <iostream>
using namespace std;

class CRC{
    public:
        string sender(string message,string crc){ //Getting message and generator bitstring
            string encoded = "";
            int m = message.length();
            int n = crc.length();
            encoded += message;
            for(int i = 0;i<n-1;i++){
                encoded+= '0';
            }
            cout<<"Final Message after extra 0's : "<<encoded<<endl;
            // Main Part Starts here
            for (int i = 0; i <= encoded.length()-n;)
            {
                for(int j = 0;j<n;j++){
                    encoded[i+j] = encoded[i+j]==crc[j]?'0':'1';
                }
                // for(;i<encoded.length() && encoded[i]!='1' ;i++);
                if(i<encoded.length() && encoded[i]!='1' ) i++;
            }
            cout<<"Remainder Obtained to be XORed with: "<<encoded<<"\n\n";
            message += encoded.substr(encoded.length()-n+1);
            cout<<"Data to be transmitted Ready! :"<<message<<"\n\n";
            return message;

            
        }

        bool receiver(string encoded,string crc){
            int m = encoded.length(),n = crc.length();
            for(int i = 0;i<=m-n;){
                for(int j = 0;j<n;j++){
                    encoded[i+j]=encoded[i+j]==crc[j]?'0':'1';

                }
                // for(;i<m && encoded[i]!='1';i++);
                if(i<m && encoded[i]!='1') i++;
            }
            cout<<"Receiver Doing Its Work Wait!\n\n";
            for (char i:encoded.substr(m-n)){
                if(i!='0'){
                    cout<<"Error In Message\n\n";
                    return false;
                }
                
            }
            cout<<"Correct Message Received\n\n";
                return true;
        }
};

int main(){
    CRC obj; //Object Creation
    string msg = "1110010101",crc="1101";//Taking An example of MEssage and CRC
    system("cls");
    cout<<"\t\t\tCyclic Redudancy Check\t\t\t\n";
    string op=obj.sender(msg,crc); //Calling Sender Function
    bool ans = obj.receiver(op,crc); //Calling Receiver Function
    return 0;
}

