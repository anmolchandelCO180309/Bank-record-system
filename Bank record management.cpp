//Basic banking record system by Anmol Chandel

#include<iostream>
#include<fstream>
#include<cstdlib>
//example for undertstanding following-> std::cout is used to use the definition of cout from std namespace.
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
class account_query
{
private:
    char account_number[20];
    char account_type[10];
    char firstName[10];
    char lastName[10];
    char Saved[5];
    float total_Balance;
public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
};
void account_query::read_data()
{
    cout<<"\nEnter Your Account Number: ";
     cin>>account_number;
    cout<<"\nEnter Type Of Account, Savings/Current: ";
    cin>>account_type;
    cout<<"\nEnter First Name: ";
    cin>>firstName;
    cout<<"\nEnter Last Name: ";
    cin>>lastName;
    cout<<"\nEnter Account Balance: ";
    cin>>total_Balance;
    cout<<"\n Saved: ";
    cin>>Saved;
    cout<<endl;
}
void account_query::show_data()
{
    cout<<"\nEntered Account Number: "<<account_number<<endl;
     cout<<"\nEnter Type Of Account, Savings/Current: ";
    cout<<"\nFirst Name: "<<firstName<<endl;
    cout<<"\nLast Name: "<<lastName<<endl;
    cout<<"\nYour Current Balance: Rs.  "<<total_Balance<<endl;
    cout<<"\n Saved: ";
    cin>>Saved;
    cout<<"-------------------------------"<<endl;
}
void account_query::write_rec()
{
    ofstream outfile;
    outfile.open("record.bank", ios::binary|ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}
void account_query::read_rec()
{
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n****Data from file****"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            show_data();
        }
    }
    infile.close();
}
void account_query::search_rec()
{
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    show_data();
}
void account_query::edit_rec()
{
    int n;
    fstream iofile;
    iofile.open("record.bank", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"Record "<<n<<" has following data"<<endl;
    show_data();
    iofile.close();
    iofile.open("record.bank", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    read_data();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void account_query::delete_rec()
{
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank", ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0; i<count; i++)
    {
        infile.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("tmpfile.bank", "record.bank");
}
int main()
{
    account_query A;
    int choice;
                      cout << "\n\n \t\t                                 Welcome To Bank Management system" << endl << endl;
    cout <<"\t                                    <><><><><><><><><><><><><><><><><><><><><><><>\n";
    cout << "\t                                               A Tradition of Trust..\n \t                                            Relationship Beyond Banking!!" << endl;
    cout <<"\t                                    <><><><><><><><><><><><><><><><><><><><><><><>\n";
    while(true)
    {
                                cout<<"\n\n \t\t                            Select one option below ";
                                cout<<"\n\n \t\t                              -->Add record to file";
						        cout<<"\n\n \t\t                              -->Show record from file";
						        cout<<"\n\n \t\t                              -->Search Record from file";
						        cout<<"\n\n \t\t                              -->Update Record";
						        cout<<"\n\n \t\t                              -->Delete Record";
						        cout<<"\n\n \t\t                              -->Quit";
						        cout<<"\n\n \t                              Enter your choice: ";
						        cin>>choice;
        switch(choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.search_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.delete_rec();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"\nEnter corret choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
