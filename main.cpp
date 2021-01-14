#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class product{
    public:
        string product_id ;
        string product_name;
        string product_amount;
        string product_price;
        string shelf_number;
};
class product_action: public product{    
    public:
        bool search_product(string search_key){
            //find if product with this id exists
            ifstream database("products"); 
            string id,line;
            while(getline(database,line))
            {
                id = line.substr(0,line.find('|'));
                if(id == search_key)
                {
                    database.close();
                    return 1;
                }
            }
            database.close();
            return 0;
        }
        void editproduct(string idin){
            //change the file product with id with the values inside product class
            string line,id;
            int lineno = 0;
            ifstream database("products");
            ofstream tmp;
            tmp.open("tmp");
            if(search_product(idin)){
                while(getline(database,line))
                {
                    id = line.substr(0,line.find('|'));
                    if( id == idin ){
                        tmp << product_id << '|' << product_name << '|' << product_amount << '|' << product_price << '|' << shelf_number << "|\n";
                    }else{
                        //id != idin
                        tmp << line << endl;
                    }
                }
            database.close();
            tmp.close();
            ofstream out;
            out.open("products");
            ifstream tmpp("tmp");
            while(getline(tmpp,line)){
                out << line << '\n';
            }
            out.close();
            tmpp.close();
            }
        }
        void setproduct(string idin){
            //set current product to the id
            ifstream database("products"); 
            string tmp,line;
            while(getline(database,line))
            {
                tmp = line.substr(0,line.find('|'));
                if(tmp == idin)
                {
                    int p[5],x = 0;
                    for(int i =0;i<line.length();i++){
                        if(line[i] == '|'){
                            p[x++] = i;
                        }
                    }
                    product_id = line.substr(0,p[0]);
                    product_name = line.substr(p[0]+1,(p[1]-p[0]-1));
                    product_amount = line.substr(p[1]+1,(p[2]-p[1]-1));
                    product_price = line.substr(p[2]+1,(p[3]-p[2]-1));
                    shelf_number = line.substr(p[3]+1,(p[4]-p[3]-1));
                    database.close();
                }
            }
            database.close();
        }
        void insertproduct(string idin){
            //insert in products file new product
            if(search_product(idin)){
                cout << "product exists!!" << endl;
            }else{
                ofstream database;
                database.open("products",ios::app);
                database <<idin<<'|'<<product_name<<'|'<<product_amount<<'|'<<product_price<<'|'<<shelf_number<<"|\n";
                database.close();
            }
        }
        void insertproduct(){
            //overloading without id gets the last id and add it
            ifstream database("products"); 
            string id,line;
            while(getline(database,line))
            {
                id = line.substr(0,line.find('|'));
            }
            database.close();
            if(id.empty()){
                id = "0";
            }
            int num = 0;
            num = stoi(id);
            num++;
            insertproduct(to_string(num));
        }
        void displayproducts(){
            //gets all the products inside the product file
            string tmp,line;
            ifstream database("products");
            while(getline(database,line)){
                int p[5],x = 0;
                for(int i =0;i<line.length();i++){
                    if(line[i] == '|'){
                        p[x++] = i;
                    }
                }
                cout << "product id: " << line.substr(0,p[0]) << endl <<
                " product name: " << line.substr(p[0]+1,(p[1]-p[0]-1)) << endl <<
                " product amount: " << line.substr(p[1]+1,(p[2]-p[1]-1)) << endl <<
                " product price: " << line.substr(p[2]+1,(p[3]-p[2]-1)) << endl <<
                " shelf number: " << line.substr(p[3]+1,(p[4]-p[3]-1)) << endl;
            }
            database.close();
        }
        void editamount(int num){
            //edits the current ammount of products and then calls editproduct
            int n = stoi(product_amount);
            n+= num;
            product_amount = to_string(n);
            editproduct(product_id);
        }
        int noOfProducts(){
            //count numbers of lines == no. of products
            string line;
            int i = 0;
            ifstream database("products");
            while(getline(database,line)){
                if(!line.empty())
                    i++;
            }
            return i;
        }
        void changeCurrent(string name,string amount,string price,string number){
            //change the class attributes to preform edit or insert or delete 
            product_name = name;
            product_amount = amount;
            product_price = price;
            shelf_number = number; 
        }
        void del(string idin){
            //delets current product
            string line,id;
            // int lineno = 0;
            ifstream database("products");
            ofstream tmp;
            tmp.open("tmp");
            if(search_product(idin)){
                while(getline(database,line))
                {
                    id = line.substr(0,line.find('|'));
                    if( id != idin ){
                        tmp << line << endl;
                    }
                }
            database.close();
            tmp.close();
            ofstream out;
            out.open("products");
            ifstream tmpp("tmp");
            while(getline(tmpp,line)){
                out << line << '\n';
            }
            out.close();
            tmpp.close();
            product_id = "";
            product_name = "";
            product_amount = "";
            product_price = "";
            shelf_number = "";
            }
        }
};
class store:public product_action{
    public:
        string user_id;
        string user_name;
        bool user_role;
        void setuser(string userid){
            //sets the current user
            if(isuser(userid)){
                ifstream users("users");
                string line;
                while(getline(users,line))
                {
                    string tmp = line.substr(0,line.find('|'));
                    if(tmp == userid)
                    {
                        int p[2],x = 0;
                        for(int i = 0; i < line.length();i++){
                            if(line[i] == '|'){
                                p[x++] = i;
                            }
                        }
                        user_id = line.substr(0,p[0]);
                        user_name = line.substr(p[0]+1,(p[1]-p[0]-1));
                        user_role = (bool)line[line.length()-1];
                    }
                }
                users.close();
            }
        }
        bool isuser(string userid){
            //find users file for user with that id
            ifstream users("users"); 
            string line,id;
            while(getline(users,line))
            {
                id = line.substr(0,line.find('|'));
                if(id == userid)
                {
                    users.close();
                    return 1;
                }
            }
            users.close();
            cout << "user doesn't exists!\n";
            return 0;
        }
        void adduser(string name,bool role){
            //add new user to the users file
            if(user_role){
                string line,tmp;
                int id;
                ifstream users("users");
                while(getline(users,line)){
                    for(int i = 0;line[i] != '|';i++){
                        tmp[i] = line[i];
                    }
                    id = stoi(tmp);
                    id++;
                    cout << "new id :" << id << endl;
                }
                users.close();
                ofstream out;
                out.open("users",ios::app);
                out << id << '|' << name << '|' << role << '\n';
                out.close();
            }else{
                cout << "user isnot admin" << endl;
            }
        }
        int noOfUsers(){
            //reads lines in users file == no. of users
            string line;
            int i = 0;
            ifstream users("users");
            while(getline(users,line)){
                if(!line.empty())
                    i++;
            }
            return i;
        }
        void displayusers(){
            //gets all users from the users file
            string line;
            ifstream users("users");
            while(getline(users,line)){
                cout << line.substr(0,line.rfind('|')) << endl;
            }
        }
};
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
    store mystore;
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
