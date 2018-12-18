#include <iostream>
#include <iomanip>
#include <fstream>//输入/输出文件流类
#include <cstring>

using namespace std;
const int Maxr = 100;//销售员最大数量
const int Maxb = 100;//农产品最大数量
const int Maxper = 100;//每个销售员的销售数
//销售员类
class Salesman {
private:
    int tag; //删除标记 1:已删 0:未删
    int no; //销售员代号
    char name[10]; //销售员姓名
    int sex;//0男1女
    char phone[11];//联系电话
    int salePros[Maxper];//所售农产品
public:
    Salesman() {}

    char *getname() { return name; } //获取姓名
    int gettag() { return tag; } //获取删除标记
    int getno() { return no; } //获取销售员代号
    void setname(char na[]) //设置姓名
    {
        strcpy(name, na);
    }

    void delman() { tag = 1; }//设置删除标记 1:已删 0:未删
    void addSaleMan(int n, char *na)//增加销售员
    {
        tag = 0;
        no = n;
        strcpy(name, na);
        for (int i = 0; i < Maxper; i++)
            salePros[i] = 0;
    }

    void salePro(int proNo)//卖农产品
    {
        for (int i = 0; i < Maxper; i++) {
            if (salePros[i] == 0) {
                salePros[i] = proNo;
                return;
            }
        }
    }

    /*int retbook(int bookid)//还书操作
    {
        for(int i=0;i<Maxper;i++)
        {
            if(salePros[i]==bookid)
            {
                salePros[i]=0;
                return 1;
            }
        }
        return 0;
    }*/
    void disp()//输出售货员信息
    {
        cout << setw(5) << no << setw(10) << name << "卖出产品编号（小于十位）：[";
        for (int i = 0; i < Maxper; i++)
            if (salePros[i] != 0)
                cout << salePros[i] << "|";
        cout << "]" << endl;
    }
};

//销售员库，储存销售员的全部信息
class SDatabase {
private:
    int top; //销售员记录指针
    Salesman sale[Maxr];//销售员记录
public:
    SDatabase() //构造函数，将reader.txt读到read[]中
    {
        Salesman s;
        top = -1;
        fstream file("salesman.txt", ios::in);//打开一个输入文件
        while (1) {
            file.read((char *) &s, sizeof(s));
            if (!file)break;
            top++;
            sale[top] = s;
        }
        file.close(); //关闭 文件
    }

    void clear()//删除所有销售员信息
    {
        top = -1;
    }

    int addSalesman(int n, char *na)//添加销售员时先查找是否存在
    {
        Salesman *p = query(n);
        if (p == nullptr) {
            top++;
            sale[top].addSaleMan(n, na);
            return 1;
        }
        return 0;
    }

    Salesman *query(int salesmanID)//按编号查找销售员
    {
        for (int i = 0; i <= top; i++)
            if (sale[i].getno() == salesmanID &&
                sale[i].gettag() == 0) {
                return &sale[i];
            }
        return NULL;
    }

    void disp() //输出所有销售员信息
    {
        for (int i = 0; i <= top; i++)
            sale[i].disp();
    }

    void salesmanData();//销售员库维护
    ~SDatabase() //析构函数，将slae[]写到salesman.txt文件中
    {
        fstream file("salesman.txt", ios::out);
        for (int i = 0; i <= top; i++)
            if (sale[i].gettag() == 0)
                file.write((char *) &sale[i], sizeof(sale[i]));
        file.close();
    }
};

void SDatabase::salesmanData() {
    char choice;
    char rname[20];
    int salesmanID;
    Salesman *r;
    while (choice != '0') {
        cout
                << "\n\n\t\t\t销售员 维 护\n\n\n\t\t 1 新 增\n\n\t\t 2 更 改\n\n\t\t 3 删 除\n\n\t\t 4 查 找\n\n\t\t 5 显 示\n\n\t\t 6 清空\n\n\t\t 0 退 出"
                << endl;
        cin >> choice;
        switch (choice) {
            case '1':
                cout << "输入销售员编号（小于十位）:";
                cin >> salesmanID;
                cout << "输入销售员姓名:";
                cin >> rname;
                addSalesman(salesmanID, rname);
                break;
            case '2':
                cout << "输入销售员编号（小于十位）:";
                cin >> salesmanID;
                r = query(salesmanID);
                if (r == nullptr) {
                    cout << " 该销售员不存在 " << endl;
                    break;
                }
                cout << "输入新的姓名:";
                cin >> rname;
                r->setname(rname);
                break;
            case '3':
                cout << " 输入销售员编号（小于十位）:";
                cin >> salesmanID;
                r = query(salesmanID);
                if (r == nullptr) {
                    cout << " 该销售员不存在" << endl;
                    break;
                }
                r->delman();
                break;
            case '4':
                cout << "读入销售员编号（小于十位）:";
                cin >> salesmanID;
                r = query(salesmanID);
                if (r == nullptr) {
                    cout << "该销售员不存在" << endl;
                    break;
                }
                r->disp();
                break;
            case '5':
                disp();
                break;
            case '6':
                clear();
                break;
            default:
                cout << "输入错误，请从新输入：";
                break;
        }
    }
}

//农产品类，实现对农产品的描述
class Production {
private:
    int tag;//删除标记 1:已删 0:未删
    int no;//农产品编号
    char name[20];//名称
    int price;//产品单价
public:
    Production() {}

    char *getname() { return name; }//名称
    int getno() { return no; }//获取农产品编号
    int gettag() { return tag; }//获取删除标记
    void setname(char na[])//设置名称
    {
        strcpy(name, na);
    }

    void delPro() { tag = 1; }//删除农产品
    void addPro(int n, char *na, int p)//增加农产品
    {
        tag = 0;
        no = n;
        strcpy(name, na);
        price = p;
    }
    /*int borrowbook()//借书操作
    {
        if (onshelf==1)
        {
            onshelf=0;
            return 1;
        }
        return 0;
    }*/
    /*void retbook()//还书操作
    {
        onshelf=1;
    }*/
    /*void disp()//输出图书
    {
        cout << setw(6) << no << setw(18) << name << setw(10)
             <<(onshelf==1? "在架":"已借") <<endl;
    }*/
};

//农产品库，实现对农产品的管理
class PDatabase {
private:
    int top; //记录指针
    Production production[Maxb]; //农产品记录
public:
    PDatabase()//构造函数，将txt读到Production[]中
    {
        Production b;
        top = -1;
        fstream file("Production.txt", ios::in);
        while (1) {
            file.read((char *) &b, sizeof(b));
            if (!file) break;
            top++;
            production[top] = b;
        }
        file.close();
    }

    void clear()//全删
    {
        top = -1;
    }

    int addPro(int n, char *na, int pri)//添加农产品
    {
        Production *p = query(n);
        if (nullptr == p) {
            top++;
            production[top].addPro(n, na, pri);
            return 1;
        }
        return 0;
    }

    Production *query(int proID)//查找农产品
    {
        for (int i = 0; i <= top; i++)
            if (production[i].getno() == proID && production[i].gettag() == 0) {
                return &production[i];
            }
        return nullptr;
    }

    void prodata();//农产品维护
    /*void disp()
    {
        for (int i=0;i<=top;i++)
            if (production[i].gettag()==0)
                production[i].disp();
    }*/
    ~PDatabase()//析构函数，将
    {
        fstream file("production.txt", ios::out);
        for (int i = 0; i <= top; i++)
            if (production[i].gettag() == 0)
                file.write((char *) &production[i], sizeof(production[i]));
        file.close();
    }
};

void PDatabase::prodata() {
    char choice;
    char bname[40];
    int pri;
    int proID;
    Production *b;
    while (choice != '0') {
        cout << "\n\n\n\t\t\t农产品 维 护 " << endl << endl;
        cout << "\t\t1 新 增\n \t\t2 更 改\n\t\t3 删 除\n\t\t4 查 找\n\t\t5 显 示\n\t\t6 全 删\n\t\t0 退 出" << endl;
        cin >> choice;
        switch (choice) {
            case '1':
                cout << "输入产品编号（小于十位）:" << endl;
                cin >> proID;
                cout << "输入农产品名:" << endl;
                cin >> bname;
                cout << "输入农产品单价:" << endl;
                cin >> pri;
                addPro(proID, bname, pri);
                break;
            case '2':
                cout << "输入产品编号（小于十位）:" << endl;
                cin >> proID;
                b = query(proID);
                if (b == nullptr) {
                    cout << " 该产品不存在 " << endl;
                    break;
                }
                cout << "输入新的名称:" << endl;
                cin >> bname;
                b->setname(bname);
                break;
            case '3':
                cout << " 读入产品编号（小于十位）:" << endl;
                cin >> proID;
                b = query(proID);
                if (b == nullptr) {
                    cout << " 该产品不存在" << endl;
                    break;
                }
                b->delPro();
                break;
//            case '4':
//                cout << " 读入产品编号:"<<endl;
//                cin >> proID;
//                b=query(proID);
//                if (b== nullptr)
//                {
//                    cout <<" 该图书不存在"<< endl;
//                    break;
//                }
//                b->disp();
//                break;
//            case '5':
//                disp();
//                break;
            case '6':
                clear();
                break;
            default:
                cout << "输入错误，请从新输入:";
        }
    }
}

//main() 函数的实现，程序的主界面的引导
int main() {
    char choice;
    int proID, salesmanID, sex,num,price;


    char sname[20], phone[11], pname[20], guige[20];
    SDatabase salesmanData;
    Salesman *s;
    PDatabase proData;
    Production *p;
    while (choice != '0') {
        cout << endl << endl << "\t\t\t 农产品销售 管 理 系 统\n\n\n";
        cout << "\t\t\t1 录入销售信息\n\n\t\t\t2 还 书 \n\n\t\t\t3 图 书 维 护\n\n\t\t\t4 读 者 维 护\n\n\t\t\t0 离 开" << endl;
        cin >> choice;
        switch (choice) {
            case '1':
                cout << " 请输入销售员编号（小于十位）:";
                cin >> salesmanID;
                cout << " 请输入销售员姓名:";
                cin >> sname;
                cout << " 请输入销售员性别(0男1女):";
                cin >> sex;
                cout << " 请输入销售员联系电话:";
                cin >> phone;
                cout << " 产品编号（小于十位）： ";
                cin >> proID;
                cout << " 产品名称： ";
                cin >> pname;
                cout << " 产品规格（小于20位）： ";
                cin >> guige;
                cout << " 产品数量： ";
                cin >> num;
                cout << " 产品单价： ";
                cin >> price;

                break;
            case '2':
                cout << "还书\n 读者编号（小于十位）:";
                cin >> salesmanID;
                cout << " 图书编号（小于十位）:";
                cin >> proID;
                s = salesmanData.query(salesmanID);
                if (s == NULL) {
                    cout << " 不存在该读者，不能还书" << endl;
                    break;
                }
                p = proData.query(proID);
                if (p == NULL) {
                    cout << " 不存在该图书，不能还书" << endl;
                    break;
                }
//                p->retbook();
//                s->retbook(p->getno());
                break;
            case '3':
                proData.prodata();
                break;
            case '4':
                salesmanData.salesmanData();
                break;
            default:
                cout << "输入错误，请从新输入：";
        }
    }
    return 0;
}