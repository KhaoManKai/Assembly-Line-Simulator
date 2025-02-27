#include <iostream>
using namespace std;
class Container{
    int m_value;
    public:
        Container(int value): m_value(value){
            clog << "Creating Container with " << value << endl;
        }
        Container& operator =(int value){
            clog << "setting container with " << m_value << "to " << value << endl;
            m_value = value;
            return *this;
        }
        ostream& display(ostream& ostr = cout)const{
            return ostr << m_value;
        }
        virtual ~Container() {
        clog << "Removing Container with " << m_value << endl;
        }
};
ostream& operator << (ostream& ostr, const Container& C){
     return C.display(ostr);
}

int main() {
    //clog.setstate(ios::failbit);
    Container C = 30; // the scope of C is here the main function
    cout << C << endl;
    C = 50;
    cout << C << endl;
    cout << (Container(200) = 100 ) << endl; // the scope of Containter only in here, in the sentence
    return 0;
}
