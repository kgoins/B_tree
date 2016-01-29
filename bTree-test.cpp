#include "bTree.h"

int main()
{
    bTree t(4); 

    t.insert("hi","1");
    t.insert("hey","2");
    t.insert("sup","3");
    t.insert("b", "4");
    t.insert("t", "5");
    t.insert("z", "6");
    t.insert("v", "7");
    t.insert("no", "9");
    t.insert("kl","10");
    t.insert("nope", "11");
    cout<<"Traversal of tree is" << endl;
    cout << t.toStr() << endl;

    string input = "";
    cout << "find hey?" << t.find("hey",&input) << endl;
    cout << "input: " << input << endl;

    input = "b";
    t.delete_key(input);
    cout << "Traversal of tree after removing " << input << endl;
    cout << t.toStr() << endl;
    cout << endl;

    input = "b";
    t.delete_key(input);
    cout << "Traversal of tree after removing " << input << endl;
    cout << t.toStr() << endl;
    cout << endl;

    input = "";
    cout << "found hey? " << t.find("hey", &input) << endl;
    cout << "input: " << input  << endl;



    input = "t";
    t.delete_key(input);
    cout << "Traversal of tree after removing " << input << endl;
    cout << t.toStr() << endl;
    cout << endl;

    input = "not here";
    t.delete_key(input);
    cout << "Traversal of tree after removing " << input << endl;
    cout << t.toStr() << endl;
    cout << endl;

    input = "v";
    t.delete_key(input);
    cout << "Traversal of tree after removing " << input << endl;
    cout << t.toStr() << endl;
    cout << endl;

    input = "hi";
    t.delete_key(input);
    cout << "Traversal of tree after removing " << input << endl;
    cout << t.toStr() << endl;
    cout << endl;

    return 0;
}


/*
//MAIN TEST 2

int main(int argc, char **argv) {
	bTree* bt = new bTree(3);
    string value;

	//Test cases
	bt->insert("Go","Gators");
	bt->insert("Hello","Gators");
	cout << bt->find("Go",&value) << endl;
	cout << bt->find("Hello",&value) << endl;
	cout << bt->find("hi",&value) << endl;
	bt->delete_key("Go");
	cout << bt->find("Go",&value) << endl;
    cout << bt->toStr() << endl;


	return 0;

}
*/


//MAIN TEST 3
/*
int main () {

    int op = 0;
    int size;
    string key;
    string value;
    cin>>size;

    bTree* BT = new bTree(size);
    while(op < 4) {
        cin >> op;
        switch(op) {
            case 0://Insert
                cin>>key;
                cin>>value;
                BT->insert(key,value);
                break;
            case 1://Delete
                cin>>key;
                BT->delete_key(key);
                break;
            case 2://Find
                cin>>key;
                if(BT->find(key,&value))
                    cout<<value<<endl;
                else
                    cout<<"Key Not Found\n";
                break;
            case 3://toString
                cout<<BT->toStr();
                break;
        }
    }
    delete BT;
    return 0;
}
*/

/*
//TEST 4
int main() {
    
    bTree* t = new bTree(5);
    string value;

    t->insert("hi","1");
    t->insert("hey","2");
    t->insert("sup","3");
    t->insert("b", "4");
    t->insert("t", "5");
    t->insert("z", "6");
    t->insert("v", "7");
    t->insert("no", "9");
    t->insert("kl","10");

    cout << t->toStr() << endl;

    t->find("sup",&value);
    cout << "value: " <<  value << endl;


    return 0;
}
*/

