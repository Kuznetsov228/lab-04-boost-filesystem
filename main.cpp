#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace boost::filesystem;
using namespace std;
class Count
{
public:
    string broc_id;
    string numcount;
    int NumFile;
    int day, mes, year;

    bool operator>(Count & c2)
    {
        if (year > c2.year) return true;
        else
        {
            if (year < c2.year) return false;
            if (mes > c2.mes) return true;
            else
            {
                if (mes < c2.mes) return false;
                if (day > c2.day) return true; 
                else
                {
                    return false;
                }

            }
        }
    }
   
    Count(string broc_id, string numcount, int day, int mes, int year)
    {
        NumFile=1; 
        this->broc_id=broc_id;
        this->numcount = numcount;
        this->day = day;
        this->mes = mes;
        this->year = year;

    }
};

int main(int argc, char *argv[])
{
    vector <Count> VC;
    path mainpath; 
    if (argc < 2) 
        {
        mainpath = current_path(); 
    }
    else 
    {
        mainpath = path(argv[1]); 
    }
    setlocale(LC_ALL, "rus");
    bool flag2 = false; 
    cout << mainpath << endl; 
    if (!is_directory(mainpath)) 
    {
        cout << "Error!! Directory not found!" << endl;
        system("pause");
        return 0;
    }
    for (const directory_entry& x : directory_iterator{ mainpath }) 
    { 
        if (is_directory(x.path())) 
        {
            for (const directory_entry& y : directory_iterator{ x.path() }) 
            {  
                if (is_regular_file(y.path())) 
                {
                    string name = y.path().stem().string(); 
                    string ext = y.path().extension().string();
                    int pos = name.find("balance_");  
                    if (pos == 0 && ext==".txt") 
                    {
                        if (name.length()==25) 
                            if (name[16] == '_') 
                            {

                                string numcount = name.substr(8, 8); 
                                string buf; 
                               
                                istringstream sin1(numcount); 
                                int Num, dd, mm, yy;
                                sin1 >> Num; 
                                if (sin1.fail()) continue; 
                                buf = name.substr(17, 4);  
                                
                                istringstream sin2(buf); 
                                sin2 >> yy; 
                                if (sin2.fail()) continue; 
                                if (yy < 1900) continue; 
                                buf = name.substr(21, 2); 

                                istringstream sin3(buf); 
                                sin3 >> mm; 
                                if (sin3.fail()) continue; 
                                if (mm < 1 || mm>12) continue;
                                buf = name.substr(23, 2); 

                                istringstream sin4(buf);
                                sin4 >> dd; 
                                if (sin4.fail()) continue; 
                                if (dd < 0 || dd>31) continue;

                                flag2 = true; 
                                cout << x.path().filename().string() << ' ' << y.path().filename().string() << endl;
                                bool flag = false; 
                                for (auto & pos : VC)
                                {
                                    if (pos.numcount == numcount) 
                                    {
                                        pos.NumFile++;
                                        
                                        Count C2(x.path().filename().string(), numcount, dd, mm, yy);
                                        if (C2>pos) 
                                        {
                                           
                                            pos.broc_id=C2.broc_id;
                                            pos.day=dd;
                                            pos.mes=mm;
                                            pos.year=yy;
                                        }
                                        flag = true; 
                                        break;

                                    }
                                }
                                if (!flag) 
                                {
                                    Count C2(x.path().filename().string(), numcount, dd, mm, yy);

                                    VC.push_back(C2);
                                }

                            }
                    }
                }
            }
        }
       
    }
    
    for (auto  pos : VC) 
    {
        
        cout << "broker: " << pos.broc_id << " account: " << pos.numcount << " files: " << pos.NumFile << " lastdate:" << pos.year << setfill('0') << setw(2) << pos.mes << setw(2) << pos.day << endl;
    }
    if (!flag2) 
    {
        cout << "Files not found!!!" << endl;
    }
    system("pause");
    return 1;
}
