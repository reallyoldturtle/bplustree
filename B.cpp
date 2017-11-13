#include <bits/stdc++.h>

using namespace std;

#define minD2 0
#define comp_lex(v1, v2) lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end())
#define maxS 100
#define minDegree 5

        
//global vars

ofstream opstream;
ifstream instream;
string inpFile;
string st_global;
vector<int> aux;
vector<string> blocks; 
vector<string> outputBlock;
int coutblcks;
int blksize;
int outputBlockHead;
int sizeofblocks;
int curBlockHead;
string outputfile;
int numBlocks;
string outFile2;
int btrees;


class BTreeNode 
{

    vector< vector<int> > keys;
    bool isLeaf;
    int minDeg;
    int degree;
    vector< BTreeNode* > children;
    int numKeys;

public:

    BTreeNode(int md, bool il) 
    {

        minDeg=md;
        numKeys=0;
        isLeaf=il;
        int nsize=2*minDeg-1;
        keys.resize(nsize);
        for(int i=0;i<nsize;i++)
            keys[i].resize(4);
        nsize+=1;
        children.resize(2*minDeg);
    }

    void insertNFull(vector<int> k) 
    {
        int i=numKeys-1;
        bool flag=false;
        int ssize=numKeys*2;
        if(isLeaf)
         {
            while(i>=0 && comp_lex(keys[i], k)!=0) 
            {
                keys[i+1]=keys[i];
                ssize++;
                i--;
            }
            keys[i+1]=k;
            ssize--;
            numKeys++;
        }
        else 
        {
            int key_c=0;
            while(i>=0 && comp_lex(keys[i], k)!=0)
                i--;
            ssize++;
            int d_s=2*minDeg-1;
            if(children[i+1]->numKeys==d_s) 
            {
                split_child(i+1, children[i+1]);
                ssize++;
            bool flag2=false;
            if(comp_lex(k, keys[i+1])!=0)
            {
                i++;
                flag2=true;
            }
            key_c++;
            }
            key_c++;
            // cout<<key_c++;
            children[i+1]->insertNFull(k);
        }
        flag=true;

    }

    void split_child(int i, BTreeNode *y) 
    {
        bool flag=false;
        BTreeNode *z=new BTreeNode(y->minDeg, y->isLeaf);
        int x_keys=0;
        z->numKeys=minDeg-1;
        x_keys=minDeg-1;
            x_keys++;
        for(int j=0;j<minDeg-1;j++) 
        {
            x_keys++;
            z->keys[j]=y->keys[j+minDeg];
        }

        if (y->isLeaf==false) 
        {
            x_keys++;
            //cout<<"here";
            for(int j=0;j<minDeg;j++)
                z->children[j]=y->children[j+minDeg];
        }
        
        int s_size;
        y->numKeys=minDeg-1;
        // cout<<"here2";
        s_size=0;
        for(int j=numKeys;j>=i+1;j--)
            children[j+1]=children[j];
        s_size++;
        children[i+1]=z;
        s_size= y->numKeys+1;
        for(int j=numKeys-1;j>=i;j--)
            keys[j+1]=keys[j];
        s_size++;
        keys[i]=y->keys[minDeg-1];
        // cout<<"here2";
        numKeys=numKeys+1;
        flag=true;
        // cout<<flag<<endl;
    }
    
    BTreeNode *search(vector<int> k) 
    {
        bool x_flag=false;
        int i = 0;
        int x_size=0;
        for(int p=0;p<k.size();p++)
            x_size+=2;
        while(i<numKeys && comp_lex(k, keys[i])!=0)
            i++;
        for(int p=0;p<k.size();p++)
            x_size+=2;
        if(k==keys[i])
        {
            x_size++;
            return this;
        }
        else
            x_flag=true;

        if(isLeaf==true)
            return NULL;
        else
            x_flag=true;


        x_size=1;
        //cout<<x_size;
        return children[i]->search(k);
    }
 
friend class BTree;
};

class BTree {

    BTreeNode *root;
    string x_val;
    string y_val;
    int minDeg;
public:
    BTree() {

        root=NULL;
        x_val="";
        y_val="";
        minDeg=minDegree;
    
    }

    BTreeNode* search(vector<int> k)
    {
        int count_c=0;
        if(root==NULL)
            return NULL;
        else
            return root->search(k);
        count_c++;
    }


    void insert(vector<int> k) 
    {
        bool f_val=true;
        bool flag1=true;
        if(root==NULL) 
        {
            bool f_val2=false;
            root = new BTreeNode(minDeg, true);
            root->keys[0]=k;
            f_val=false;
            // cout<<fval;
            root->numKeys=1;
            f_val2=true;
            // cout<<f_val2;
            aux.push_back(k[0]);
        }
        else 
        {
            vector <int>aux2;
            if(root->numKeys==2*minDeg-1) 
            {
                int i;
                BTreeNode *s=new BTreeNode(minDeg, false);
                aux.push_back(k[0]);
                s->children[0]=root;
                aux2.push_back(k[0]);
                aux2.push_back(0);
                s->split_child(0, root);
                i=0;
                if(comp_lex(k, s->keys[0])!=0)
                    i++;
                aux2.push_back(i);
                s->children[i]->insertNFull(k);
                aux2.push_back(i);
                root=s;
            }
            else 
            {
                root->insertNFull(k);
                aux2.push_back(k[0]);
                aux.push_back(k[0]);
            }
        }

    }
};

BTree tree;

void process(string line) 
{
    vector<int> entry;
    int x;
    int curBlockHeadIt=0;
    vector<int>::iterator it;
    x = atoi (line.c_str());
    entry.push_back(x);
    tree.insert(entry);
}

void compare(int s1, int s2)
{
    if(s1>s2)
    {

    }
        // cout<<s1;
        // cout<<s2;
}

void find(string st) 
{
    int x=0;
    x = atoi (st.c_str());
    vector<int> record1;
    record1.push_back(x);
    (tree.search(record1))?opstream<<"YES"<<"\n":opstream<<"NO"<<"\n";
}


void countrange(vector < int> &a, vector < int> &b)
{    
    vector <int> :: iterator it;
    int count=0;
   //cout<<"ihere";
    it=a.begin();
    int s1=a.size();
    int s2=b.size();
    while(it!=a.end())
    {
        s1++;
        if((*it <= b[1]) &&  (*it >= b[0]))
            count+=1;
        compare(s1,s2);
        it++;
    }
    //cout<<count<<endl;
    opstream<<count<<"\n";
}


void count(vector < int> &a, int val)
{
    int count_val=0;
    count_val = count (a.begin(), a.end(), val);
    opstream<<count_val<<"\n";

}


void btree_compute() 
{

    string line;
    vector<int> record;

    while(getline(instream, line))
     { 

        size_t pos1 = line.find("INSERT");
        size_t pos2 = line.find("FIND");
        size_t pos3 = line.find("COUNT");
        size_t pos4 = line.find("RANGE");
        int ins=7;
        int fin=5;
        int co=6;
        int r=6;
        //for insert
        if(pos1 != -1)
        {

            line = line.substr (ins);
            blocks[curBlockHead++]=line;
            ins=0;
            process(line);

        }   
        // for find
        if(pos2 != -1)
        {

            line = line.substr (fin);
            fin=0;
            find(line);
        }
        // for count
        if(pos3 != -1)
        {
            int val=0;
            line = line.substr (co);
            const char * ch = line.c_str();
            val = atoi(ch);
            co=0;
            count(aux,val);
        }
        
        // for range
        if(pos4 != -1)
        {

            string ncr;
            line = line.substr (r);
            stringstream linestream(line);
            co=0;
            int x;
            while(getline(linestream, ncr, ' ')) 
            {
                // int x=0;
                x = atoi (ncr.c_str());
                record.push_back(x);
            }   
            x=0;
            countrange(aux,record);
        }

    }

}




int main(int argc, char* argv[])
{
    int num,value_enter;
    bool new_flag=false;
    if(argc==5) 
    {
    inpFile = argv[1];
    string b_size=argv[3];
    blksize = atoi(argv[3]);
    string n_blocks=argv[2];
    numBlocks = atoi(argv[2]);
    outputfile = argv[4];
    outputBlockHead=0;
    opstream.open(outputfile.c_str());
    instream.open(inpFile.c_str());
    curBlockHead=0;
    blocks.resize(blksize*(numBlocks-1));
    num=0;
    outputBlock.resize(blksize);
    btree_compute();
    new_flag=true;
    sort (aux.begin(), aux.end());
    }
    else
    {
        cout<<"Invalid number of arguments!\n";
    }

    return 0;
}