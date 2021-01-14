#include<iostream>
#include<fstream>
#include<string.h>
#include"inventory.h"
using namespace std;

void cls(){
    //clear screen
    system("cls");
}
int main(){
    ofstream f1("products",ios::app);
    f1.close();
    ofstream f2("users",ios::app);
    f2.close();
    ofstream f3("tmp",ios::app);
    f3.close();
    inv::store mystore;
    mystore.user_role = 1;
    int c,i = 0,nou,nop,num;
    string tmp1,tmp2,tmp3,tmp4,tmp5;
    cls();
    while(1){
        loop:
        if(i == 0){
            nou = mystore.noOfUsers();
            if(nou == 0){
                cout << "first login:\n enter your name: ";cin >> tmp1;
                mystore.adduser(tmp1,1);
            }
            nou = mystore.noOfUsers();
            cout << "number of users: " << nou << endl;
            cout << "1.login\n2.create user" << endl;
            cout << "choice: ";cin >> c;
            switch(c){
                case 1:
                    mystore.displayusers();
                    cout << "login: \n id: ";
                    cin >> tmp1;
                    mystore.setuser(tmp1);
                    i++;
                    break;
                case 2:
                    cout << "create user:\n enter your name: ";
                    cin >> tmp1;
                    mystore.adduser(tmp1,0);
                    goto loop;
                    break;
                default:
                    goto exit;
            } 
        }
        cls();
        nop = mystore.noOfProducts();
        cout << "number of products: " << nop << endl;
        if(nop == 0){
            cout << "1.add product\n";
            cout << "choice: ";cin >> c;
            if(c == 1){
                cout << "enter the following:\n name: ";
                cin >> tmp1;
                cout << " amount: ";
                cin >> tmp2;
                cout << " price: ";
                cin >> tmp3;
                cout << " shelf number : ";
                cin >> tmp4;
                mystore.changeCurrent(tmp1,tmp2,tmp3,tmp4);
                mystore.insertproduct();
                goto loop;
            }else{
                goto exit;
            }
        }
        mystore.displayproducts();
        cout << "1.add product\n2.select product\nchoice: ";cin >> c;
        switch(c){
            case 1:
                cout << "enter the following:\n name: ";
                cin >> tmp1;
                cout << " amount: ";
                cin >> tmp2;
                cout << " price: ";
                cin >> tmp3;
                cout << " shelf number : ";
                cin >> tmp4;
                mystore.changeCurrent(tmp1,tmp2,tmp3,tmp4);
                mystore.insertproduct();
                break;
            case 2:
                cout << "enter product id: ";
                cin >> tmp1;
                mystore.setproduct(tmp1);
                cout << "1.add amount\n2.remove amount\n3.edit product\n4.delete product\nchoice: ";
                cin >> c;
                switch (c)
                {
                case 1:
                    cout << "enter amount: ";cin >> num;
                    mystore.editamount(num);
                    break;
                case 2:
                    cout << "enter amount: ";cin >> num;
                    mystore.editamount(num*-1);
                    break;
                case 3:
                    cout << "enter the following new values:\n name: ";
                    cin >> tmp2;
                    cout << " amount: ";
                    cin >> tmp3;
                    cout << " price: ";
                    cin >> tmp4;
                    cout << " shelf number : ";
                    cin >> tmp5;
                    mystore.changeCurrent(tmp2,tmp3,tmp4,tmp5);
                    mystore.editproduct(tmp1);
                    break;
                case 4:
                    char ch;
                    cout << "are you sure you want to delete product number " << tmp1 << endl;
                    cout << "y/n ";cin >> ch;
                    if(ch == 'y'){
                        mystore.del(tmp1);
                    }
                default:
                    goto loop;
                    break;
                }
                break;
            default:
                goto loop;
                break;
        }
    }
    exit:
    cout << "exitting..." << endl;
    return 0;
}