#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Node{
    string  Name;
    string Age;
    string Id;
    string phone_number;
    string email_add;
    Node *next;
    Node(string name="", string number="",string email="", string age=0 , string id=""):Name(name), Age(age), Id(id), phone_number(number),email_add(email), next(nullptr){};
};

bool are_equal(string var, string var2){
    return var.compare(var2)==0;
}

class linked_list{
private:
    Node *head = nullptr, *tail = nullptr;
    size_t  length=0;

public:

    void add_node(string name,string number, string email, string age, string id){
        Node *node = new Node(name,number, email, age, id);
        if (!head){
            head = tail = node;
        }
        else{
            tail->next = node;
            tail = node;
        }
        length++;
    }

    void add_to_firstpos(string name, string number, string email, string age, string id){
        Node *node = new Node(name,number, email, age, id);
        node->next = head;
        head = node;
        length++;
    }

    void add_to_lastpos(string name,string number, string email, string age, string id){
        Node *node = new Node(name,number, email, age, id);
        if(!head)
            head = tail = node;
       else{
            tail->next = node;
            tail = node;
       }
        length++;
    }

    void add_at_pos (string name,string number, string email, string age, string id,int pos){
        Node *node = new Node(name,number, email, age, id);
        if(pos < 1 || pos > return_length()+1){
            cout<<"Can not be added to this postion, out of limit !!!"<<endl;
            return;
        }
        if(pos == 1){
            add_to_firstpos(name,number,email, age, id);
            return;
        }
        if(pos == return_length()+1){
            add_to_lastpos(name, number, email, age, id);
            return;
        }
        else{
            Node *temp = head;
            for(int i = 1; i < pos - 1; ++i){
                temp = temp->next;
            }
        node->next = temp->next;
        temp->next = node;
        }

        length++;
    }

    void remove_first(){
        if(!head){
            cout<<"\a No items exist to be cleared"<<endl;
            return;
        }

        Node *del = head;
        head = head->next;
        delete del;
        
        if(!head)
            tail = nullptr;
        length--;
        cout<<"Item has been removed :)"<<endl;
    }

    void remove_last(){
        if(!head){
            cout<<"\a No items exist to be cleared"<<endl;
            return;
        }
        if(head==tail && head != nullptr){
           delete head;
            head = tail = nullptr;
            length = 0;
        }else{
            Node *temp = head;
            while(temp->next != tail)
                temp = temp->next;
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        length--;
    }
   
    void remove(string name){
        if (!head) {
            cout << "\aNo items exist to be cleared" << endl;
            return;
        }

        if (are_equal(head->Name, name)) {
            remove_first();
            return;
        }

        Node *mov = head;

        while (mov->next && !are_equal(mov->next->Name, name)) {
            mov = mov->next;
        }

        if (mov->next) {
            Node *del = mov->next;
            mov->next = del->next;

            if (del == tail) {
                tail = mov;
            }

            delete del;
            length--;
            cout << "Item has been found and removed from the list." << endl;
            }else {
            cout << "\aItem with this name is not existing; can't be removed!" << endl;
            }
    }

    void clear_list(){
        if(!head){
            cout<<"\a No items exist to be cleared"<<endl;
            return;
        }
        Node *temp = head;
        while(temp){
                Node *curr = temp->next;
                delete temp;
                temp = curr;        
        }
        head = tail = nullptr;
        length = 0;
        cout<<"List has been cleared"<<endl;
    }

    void search_for(string wanted){
        if(!head){
            cout<<"\a No items exist to search for!"<<endl;
            return;
        }

        Node *mov = head;
        while(mov && mov->Name != wanted){
            mov = mov->next;
        }
       
        if (mov){
            cout<<"Item Exits :), and here is its data ----> \n";
            cout<<"Item name is: "<< mov->Name<<endl;
            cout<<"Item number : "<< mov->phone_number<<"\t\t\t Item email is : "<<mov->email_add<<endl;
            cout<<"Item age : " << mov->Age << "\t\t\t Item id : "<<mov->Id<<endl;
        }
        else
            cout<<"\aItem with this name is not existing; can't be removed !"<<endl;
    }

    int return_length(){
        return length;
    }

    void display_list(){
        if(!head)
            cout<<"\aNo items here to display !!!!"<<endl;
        Node *temp = head;
        while (temp){
            cout<<"Name : "<<temp->Name<<endl;
            cout<<"number is : "<<temp->phone_number<<"\t\t\t\t email is:"<<temp->email_add<<endl;
            cout<<"Age : "<<temp->Age << "\t\t\t\t" << "Id : "<<temp->Id <<endl;
            temp = temp->next;
        }
    }

    void save_to_file(const string &filename = "contacts.txt") {
       ofstream out(filename, ios::app);
        if (!out) {
            cout << "Error opening file to save!" << endl;
            return;
        }

        Node *temp = head;
        while (temp) {
            out << temp->Name << "," <<temp->phone_number << "," <<temp->email_add << "," << temp->Age << "," << temp->Id <<"\n";
            temp = temp->next;
        }

        out.close();
        cout << "Contacts saved to file." << endl;
    }

    void load_from_file(const string& filename = "contacts.txt") {
        ifstream file(filename);
        if (!file) {
            cout << "File not found. Starting with empty contact list." << endl;
            return;
        }

        string line, name, number, email, age, id;
        while (getline(file, line)) {
            if (line.rfind("Name: ", 0) == 0)
                name = line.substr(6);
            else if (line.rfind("Phone: ", 0) == 0)
                number = line.substr(7);
            else if (line.rfind("Email: ", 0) == 0)
                email = line.substr(7);
            else if (line.rfind("Age: ", 0) == 0)
                age = line.substr(5);
            else if (line.rfind("Id: ", 0) == 0)
                id = line.substr(4);
            else if (line == "---") {
                add_to_lastpos(name, number, email, age, id);
            }
        }
        file.close();
    }

    ~linked_list(){
        clear_list();
    }
};

int main(){
    int choice, pos, insertion;
    linked_list ls;
    // ls.load_from_file();
    string name, number, email, age, id;
    while(true){
        cout<<"Hello what do you want to do ??"<<endl;
        cout<<"1. Add a new user \n";
        cout<<"2. Search for a user\n";
        cout<<"3. Remove a user \n";
        cout<<"4. Display all users\n";
        cout<<"5. Clear whole list \n";
        cout<<"6. Exit \n";
        cout<<"Enter you choice.....";
        cin>>choice;
        switch (choice){
            case 1:
                cin.ignore();
                cout<<"Enter name: ";
                getline(cin,name);
               
                cin.ignore();
                cout<<"Enter phone number : ";
                cin>>number;
               
                cin.ignore();
                cout<<"Enter Email address : ";
                cin>>email;

                cin.ignore();
                cout<<"Enter Age : ";
                cin>>age;

                cin.ignore();
                cout<<"Enter ID : ";
                cin>>id;
                
                cout<<"Where to add it ?? (1.first/2.last/3.specific/any) : ";
                cin>>pos;
                switch (pos)
                {
                    case 1:
                        ls.add_to_firstpos(name,number,email,age, id);
                        ls.save_to_file();
                        break;
                    case 2:
                        ls.add_to_lastpos(name, number, email, age, id);
                       ls.save_to_file();
                        break;
                    case 3:
                        cout<<"Enter Position to insert at: ";
                        cin>>insertion;
                        ls.add_at_pos(name,number, email,age, id,insertion);
                        ls.save_to_file();
                        break;
                    default:
                        ls.add_node(name,number,email, age, id);
                        ls.save_to_file();
                        break;
                    }
                break;
            case 2:
                cin.ignore();
                cout<<"Enter name to search for: ";
                getline(cin, name);
                ls.search_for(name);
                break;
            case 3:
                cin.ignore();
                cout<<"Enter name to delete: ";
                getline(cin, name);
                ls.remove(name);
                ls.save_to_file();
                break;
            case 4:
                ls.display_list();
                break;
            case 5:
                ls.clear_list();
                ls.save_to_file();
                break;
            case 6:
                exit(0);
                break;
            default:
                cout<<"\aDid not get a valid input !!!\n";
                break;
        }
   }
   return 0;
}