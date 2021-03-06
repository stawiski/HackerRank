#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person {
    public:
        virtual void getdata() {
            cin >> name;
            cin >> age;
        }
        virtual void putdata() {
           cout << name << " " << age << " ";
        }
    protected:
        string name;
        int age;
};

class Professor: public Person {
    public:
        Professor() {
            /* Increase unique id and assign it to current id. */
            this->cur_id = ++this->id;
        }
        void getdata() {
            Person::getdata();
            cin >> publications;
        }
        void putdata() {
            Person::putdata();
            cout << publications << " " << cur_id << endl;
        }
    protected:
        int publications;
        int cur_id;
    private:
        static int id;
};

int Professor::id = 0;

class Student: public Person {
    public:
        Student() {
            /* Increase unique id and assign it to current id. */
            this->cur_id = ++this->id;
        }
        void getdata() {
            Person::getdata();
            marksSum = 0;
            /* Loop through 6 marks. */
            for (int i = 0; i < 6; i++) {
                cin >> marks[i];
                /* Calculate mark sum. */
                marksSum += marks[i];
            }
        }
        void putdata() {
            Person::putdata();
            cout << marksSum << " " << cur_id << endl;
        }
    protected:
        int marks[6];
        int marksSum;
        int cur_id;
    private:
        static int id;
};

int Student::id = 0;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}
