#include <iostream>
#include <fstream>
#include <iomanip> // for setw() function
using namespace std;

class account
{
    int acc_no;
    char acc_name[20];
    int dep;
    char acc_type;
public:
    void create_acc();
    void display_acc();
    void modify_acc();
    void deposit_acc(int);
    void withdraw_acc(int);
    void all_acc();         // function for displaying all the accounts in tabular form
    int ret_acc()
    {
        return acc_no;
    }
    int ret_dep()
    {
        return dep;
    }
    char ret_type()
    {
        return acc_type;
    }
};
void account::create_acc()
{
    cout<<" \n Enter the account no: ";
    cin>>acc_no;
    cout<<" \n Enter the name of the account holder: ";
    cin.ignore();
    cin.getline(acc_name,20);
    cout<<" \n Enter the account type (c/s): ";
    cin>>acc_type;
    cout<<" \n Enter the amount you want to initially deposit: ";
    cin>>dep;
    cout<<" \n\n Account Created ";
    cout<<endl;
}
void account::display_acc()
{
    cout<<" \n Account no: ";
    cout<<acc_no;
    cout<<" \n Account holder name: ";
    cout<<acc_name;
    cout<<" \n Account type: ";
    cout<<acc_type;
    cout<<" \n Balance Amount: ";
    cout<<dep;
    cout<<endl;
}
void account::modify_acc()
{
	cout<<" \n Account no: ";
	cout<<acc_no;
	cout<<" \n New modified account holder name: ";
	cin.ignore();
	cin.getline(acc_name,20);
	cout<<" \n New modified type of account (c/s): ";
	cin>>acc_type;
	cout<<" \n New modified balance amount: ";
	cin>>dep;
	cout<<endl;
}
void account::deposit_acc(int x)
{
    dep=dep+x;
    cout<<endl;
}
void account::withdraw_acc(int y)
{
    dep=dep-y;
    cout<<endl;
}
void account::all_acc()
{
    cout<<" "<<acc_no<<setw(10)<<" "<<acc_name<<setw(6)<<" "<<acc_type<<setw(15)<<dep<<endl;
}

class bank
{
    account a;
    ofstream fout;
    ifstream fin;
    fstream f;
public:
    void write();
    void output();
    void modify();
    void delete_single();
    void all();             // displaying all accounts in tabular form
    void deposit();
    void withdraw();
};
void bank::write()
{
    fout.open("acc.dat",ios::binary|ios::app);
    if(fout)
    {
        a.create_acc();
        fout.write((char*)&a,sizeof(a));
    }
    fout.close();
    if(!fout)
    {
        cout<<" \n File does not exist ";
    }
}
void bank::output()
{
    int n,flag=0;
    cout<<" \n Enter the account no to be displayed: ";
    cin>>n;
    fin.open("acc.dat",ios::binary);
    while(fin.read((char*)&a,sizeof(a)))
    {
        if(a.ret_acc()==n)
        {
            a.display_acc();
            flag=1;
        }
    }
    fin.close();
    if(flag==0)
    {
        cout<<" \n Wrong account no ";
    }
}
void bank::modify()
{
    int n,flag=0;
    cout<<" \n Enter the account no to be modified: ";
    cin>>n;
    f.open("acc.dat",ios::binary|ios::in|ios::out);
    while(f.read((char*)&a,sizeof(a)))
    {
        if(a.ret_acc()==n)
        {
            a.display_acc();
            cout<<" \n Enter the modified details ";
            a.modify_acc();
            double pos=-1*sizeof(a);
            f.seekp(pos,ios::cur);
            f.write((char*)&a,sizeof(a));
            flag=1;
            cout<<" \n Record updated ";
        }
    }
    f.close();
    if(flag==0)
    {
        cout<<" \n Wrong account no ";
    }
}
void bank::deposit()
{
    int n,flag=0,amt;
    cout<<" \n Enter the account no in which money to be deposited: ";
    cin>>n;
    f.open("acc.dat",ios::binary|ios::in|ios::out);
    while(f.read((char*)&a,sizeof(a)))
    {
        if(a.ret_acc()==n)
        {
            a.display_acc();
            cout<<" \n Enter the amount to be deposited: ";
            cin>>amt;
            a.deposit_acc(amt);
            double pos=-1*sizeof(a);
            f.seekp(pos,ios::cur);
            f.write((char*)&a,sizeof(a));
            flag=1;
            cout<<" \n Record updated ";
        }
    }
    f.close();
    if(flag==0)
    {
        cout<<" \n Wrong account no ";
    }
}
void bank::withdraw()
{
    int n,flag=0,amt;
    cout<<" \n Enter the account no in which money to be withdrawn: ";
    cin>>n;
    f.open("acc.dat",ios::binary|ios::in|ios::out);
    while(f.read((char*)&a,sizeof(a)))
    {
        if(a.ret_acc()==n)
        {
            a.display_acc();
            cout<<" \n Enter the amount to be withdrawn: ";
            cin>>amt;
            a.withdraw_acc(amt);
            cout<<" After withdraw";
            a.display_acc();
            double pos=-1*sizeof(a);
            f.seekp(pos,ios::cur);
            f.write((char*)&a,sizeof(a));
            flag=1;
            cout<<" \n Record updated ";
        }
    }
    f.close();
    if(flag==0)
    {
        cout<<" \n Wrong account no ";
    }
}
void bank::all()
{
    fin.open("acc.dat",ios::binary);
    if(!fin)
    {
         cout<<" \n File does not exist ";
    }
    else
    {
        cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
        cout<<"==========================================================\n";
        cout<<" ACC NO.          NAME              TYPE        BALANCE\n";
        cout<<"==========================================================\n";
        while(fin.read((char*)&a,sizeof(account)))
        {
            a.all_acc();
        }
    }
    fin.close();
}

void bank::delete_single()
{
    int n,flag=0;
    cout<<" \n Enter the account no to be deleted: ";
    cin>>n;
    fout.open("new.dat",ios::binary);
    fin.open("acc.dat",ios::binary);
    while(fin.read((char*)&a,sizeof(a)))
    {
        if(a.ret_acc()!=n)
        {
            fout.write((char*)&a,sizeof(a));
            flag=1;
        }
    }
    fout.close();
    fin.close();
    remove("acc.dat");
    rename("new.dat","acc.dat");
    if(flag==0)
    {
        cout<<" \n Wrong account no ";
    }
    if(flag==1)
    {
        cout<<" \n Record deleted ";
    }
}

int main()
{
    bank b;
    cout<<"\n\n \t****************";
    cout<<" \n\t*     BANK     * \n";
    cout<<" \t*  MANAGEMENT  * \n";
    cout<<" \t*    SYSTEM    * \n";
    cout<<" \t****************"<<endl;
    int c;
    do
    {
        cout<<"\n\n\t MENU \n";
        cout<<"\n  1. NEW ACCOUNT";
		cout<<"\n  2. DEPOSIT AMOUNT";
		cout<<"\n  3. WITHDRAW AMOUNT";
		cout<<"\n  4. BALANCE ENQUIRY";
		cout<<"\n  5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n  6. CLOSE AN ACCOUNT";
		cout<<"\n  7. MODIFY AN ACCOUNT";
		cout<<"\n  8. EXIT";
		cout<<"\n Select Your Option (1-8): ";
		cin>>c;
		cout<<endl;
		switch(c)
		{
            case 1: b.write();
                    break;
            case 2: b.deposit();
                    break;
            case 3: b.withdraw();
                    break;
            case 4: b.output();
                    break;
            case 5: b.all();
                    break;
            case 6: b.delete_single();
                    break;
            case 7: b.modify();
                    break;
            case 8: cout<<" \n\n THANK YOU \n\n";
                    break;
            default: cout<<" \n ENTER VALID CHOICE \n ";
		}
		cin.ignore();
    }while(c!=8);
    return 0;
}
