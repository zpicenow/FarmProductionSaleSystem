#include <iostream>
#include <iomanip>
#include <fstream>//输入/输出文件流类
#include <cstring>
#include <map>

using namespace std;
const int Maxr = 100;//销售员最大数量
const int Maxb = 100;//农产品最大数量
const int Maxper = 100;//每个销售员的销售数
const int MaxMouth = 100;//最多100个月数据

//销售员类
class Salesman {
private:
    int tag; //删除标记 1:已删 0:未删
    int no; //销售员代号
    string name; //销售员姓名
    int sex;//0男1女
    string phone;//联系电话
    map<int,int> saleProsMap; //所售农产品
//    int salePros[Maxper];
public:
    Salesman() {}

    string getname() { return name; } //获取姓名
    int gettag() { return tag; } //获取删除标记
    int getno() { return no; } //获取销售员代号
    void setname(string na) //设置姓名
    {
        name = na;
    }

    void delman() { tag = 1; }//设置删除标记 1:已删 0:未删
    void addSaleMan(int n, string na, int se, string ph)//增加销售员
    {
        tag = 0;
        no = n;
        sex = se;
        name = na;
        phone = ph;


    }

    void salePro(int proNo,int num)//卖农产品
    {

        saleProsMap.insert(pair<int, int>(proNo, num));
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
        cout << setw(5) << no << setw(10) << name << "卖出产品：[";
        map<int, int>::iterator iter;
        for(iter = saleProsMap.begin(); iter != saleProsMap.end(); iter++)

            cout<<iter->first<<' X '<<iter->second<<endl;
        cout << "]" << endl;
    }
};

//销售员库，储存销售员的全部信息
class SDatabase {
//销售员记录指针
    //销售员记录
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

    int addSalesman(int n, string na, int se, string ph)//添加销售员时先查找是否存在
    {

        Salesman *p = query(n);
        if (p == nullptr) {
            top++;
            sale[top].addSaleMan(n, na, se, ph);
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

    Salesman sale[Maxr];
    int top;
};

void SDatabase::salesmanData() {
    char choice;
    string rname,phone;
    int salesmanID;
    int sex;
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
                cout << "输入销售员性别(0男1女):";
                cin >> sex;
                addSalesman(salesmanID, rname, sex,phone);
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
    string  name;//名称
    int num;
    int price;//产品单价
    int priceTol;
public:
    Production() {}

    string getname() { return name; }//名称
    int getno() { return no; }//获取农产品编号
    int gettag() { return tag; }//获取删除标记

    void addpriceTol(int tol)//设置名称
    {
        priceTol += tol;
    }

    void delPro() { tag = 1; }//删除农产品
    void addPro(int n, string na, int p,int nu)//增加农产品
    {
        tag = 0;
        no = n;
        name = na;
        price = p;
        num = nu;
        priceTol = p * nu;
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
public:
    int top; //记录指针
    Production production[Maxb]; //农产品记录
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

    int addPro(int n, string na, int pri,int nu)//添加农产品
    {
        Production *p = query(n);
        if (nullptr == p) {
            top++;
            production[top].addPro(n, na, pri,nu);
            return 1;
        } else {
            p->addpriceTol(pri * nu);
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
//月数据
class Mouth {
private:
    int saleID,proID,mouth,num,price,priceTol;
    string salename,proname;//名称
public:

    int getSaleID() { return saleID; }
    int getProID() { return proID; }
    int getMouth() { return mouth; }
    int getNum() { return num; }
    int getPrice() { return price; }

    void addMouthMes(int sid,int pid,int mou,int pri,int nu,string sname,string pname)
    {
        saleID = sid;
        proID = pid;
        mouth = mou;
        price = pri;
        num = nu;
        salename = sname;
        proname = pname;
        priceTol = pri * nu;
    }
    void disp()//输出
    {
        cout << setw(10) << saleID << setw(10) << salename << setw(10) << proID << setw(10) << proname
             << mouth << setw(10) << price << setw(10) << num << setw(10) << priceTol << endl;
    }
};

//月销量库，
class MouthDataBase {
private:
public:
    int top = -1; //记录指针
    Mouth mouth[MaxMouth]; //记录


    void clear()//全删
    {
        top = -1;
    }

    int addMouthData(int sid,int pid,int mou,int pri,int nu,string sname,string pname)//添加
    {
        Mouth *p = query(sid,pid,mou);
        if (nullptr == p) {
            top++;
            mouth[top].addMouthMes(sid,pid,mou,pri,nu,sname,pname);
            return 1;
        }
        return 0;
    }

    Mouth *query(int sid,int pid,int mou)//查找
    {
        for (int i = 0; i <= top; i++)
            if (mouth[i].getSaleID() == sid && mouth[i].getProID() == pid && mouth[i].getMouth() == mou) {
                return &mouth[i];
            }
        return nullptr;
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
    int proID, salesmanID, sex, num, price, priceTol,date;

    string phone, pname;

    char sname[20], guige[20];
    SDatabase salesmanData;
    Salesman *s;
    PDatabase proData;
    Production *p;
    MouthDataBase mouthDataBase;
    Mouth *m;
    while (choice != '0') {
        cout << endl << endl << "\t\t\t 农产品销售 管 理 系 统\n\n\n";
        cout << "\t\t\t1 录入销售信息\n\n\t\t\t2 销售员维护 \n\n\t\t\t3 销售信息管理\n\n\t\t\t4 读 者 维 护\n\n\t\t\t0 离 开" << endl;
        cin >> choice;
        switch (choice) {
            case '1':
                cout << " 请输入销售员编号（小于十位）:";
                cin >> salesmanID;
                cout << " 请输入销售员姓名:";
                cin >> sname;
                cout << " 请输入销售员性别(0男1女):";
                cin >> sex;
                while (sex != 0 && sex != 1) {
                    cout << "性别无效请重新输入" << endl;
                    cin >> sex;
                }
                cout << " 请输入销售员联系电话:";
                cin >> phone;
                while (phone.length() > 11) {
                    cout << "电话无效，请重新输入" << endl;

                    cin >> phone;

                }
                cout << " 产品编号（小于十位）： ";
                cin >> proID;
                cout << " 产品名称： ";
                cin >> pname;
                while (pname == " ") {
                    cout << "名称无效重新输入" << endl;

                    cin >> pname;

                }
                cout << " 产品规格（小于20位）： ";
                cin >> guige;
                cout << " 产品数量： ";
                cin >> num;
                cout << " 产品单价： ";
                cin >> price;

                cout << " 销售日期(格式20190101)： ";
                cin >> date;
                salesmanData.addSalesman(salesmanID, sname, sex, phone);
                proData.addPro(proID, pname, price);
                salesmanData.sale[salesmanData.top].salePro(proID, num);
                mouthDataBase.addMouthData(salesmanID, proID, date / 100, price, num, sname, pname);
                break;
            case '2':
                salesmanData.salesmanData();
                break;
            case '3':
                int sID;
                cout << "请输入销售员代号" << endl;
                cin >> sID;
                salesmanData.query(sID)->disp();
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