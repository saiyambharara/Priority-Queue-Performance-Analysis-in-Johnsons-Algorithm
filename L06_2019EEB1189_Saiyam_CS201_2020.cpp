#include<bits/stdc++.h>
#include<time.h>
#define pb push_back
using namespace std;

vector<pair<long long int,long long int>> adj[100000],adjlist[100000],heap;
map<long long int,long long int> m;
long long int dist[100000]={0},sp[1000][1000],dd[100000],vis[100000];
//binary
void H1insert(long long int k,long long int v) 
{ 
    heap.pb({k,v});
    m[k]=heap.size()-1;
    long long int i=heap.size()-1;
    while (i!=0&&heap[(i-1)/2].second>heap[i].second) 
    { 
       long long int t=m[heap[(i-1)/2].first];
       m[heap[(i-1)/2].first]=m[heap[i].first];
       m[heap[i].first]=t;
       pair<int,int> p=heap[(i-1)/2];
       heap[(i-1)/2]=heap[i];
       heap[i]=p; 
       i=(i-1)/2; 
    } 
} 
void H1minheapify(long long int i) 
{ 
    long long int l=2*i+1,r=2*i+2; 
    long long int s=i; 
    if(l<heap.size()&&heap[l].second<heap[i].second) 
    s=l; 
    if(r<heap.size()&&heap[r].second<heap[s].second) 
    s=r; 
    if(s!=i) 
    { 
        long long int t=m[heap[s].first];
        m[heap[s].first]=m[heap[i].first];
        m[heap[i].first]=t;
        pair<long long int,long long int> p=heap[s];
        heap[s]=heap[i];
        heap[i]=p; 
        H1minheapify(s); 
    } 
} 
pair<long long int,long long int> H1extractmin() 
{  
    if (heap.size()==1) 
    { 
        pair<long long int,long long int> p=heap.back();
        heap.pop_back();
        m.erase(p.first);
        return p; 
    } 
    vis[heap[0].first]=0;
    pair<long long int,long long int> root=heap[0]; 
    heap[0]=heap.back(); 
    m[heap[0].first]=0;
    heap.pop_back(); 
    m.erase(root.first);
    H1minheapify(0); 
  
    return root; 
} 
void H1decreasekey(long long int k,long long int v)
{
    long long int i=m[k];
    heap[i].second=v;
    while(i!=0&&heap[(i-1)/2].second>heap[i].second)
    {
        long long int t=m[heap[(i-1)/2].first];
        m[heap[(i-1)/2].first]=m[heap[i].first];
        m[heap[i].first]=t; 
        pair<int,int> s=heap[(i-1)/2];
        heap[(i-1)/2]=heap[i];
        heap[i]=s;
        
        i=(i-1)/2;
    }
}
long long int H1empty()
{
    if(heap.size()==0)
    return 1;
    else
    return 0;
}
//----------------------------
//binomial
struct Node 
{ 
    long long int val,degree,pos; 
    Node *parent;
    Node *child;
    Node *sibling; 
} *root=NULL; 

Node *H2merge(Node *a, Node *b) 
{ 
    if (a==NULL) 
    return b; 
    if (b==NULL) 
    return a; 
    Node *temp=NULL; 
    Node *back=temp;
    if(a->degree<=b->degree)
    {
        back=a;
        a=a->sibling;
        back->sibling=NULL;
    }
    else
    {
        back=b;
        b=b->sibling;
        back->sibling=NULL;
    }
    temp=back;
    while(a&&b)
    {
        if(a->degree<=b->degree)
        { 
            back->sibling=a;
            a=a->sibling;
            back=back->sibling;
            back->sibling=NULL;
        }
        else
        {
            back->sibling=b;
            b=b->sibling;
            back=back->sibling;
            back->sibling=NULL;
        }
    }
    while(a)
    {
        back->sibling=a;
        a=a->sibling;
        back=back->sibling;
        back->sibling=NULL;
    }
    while(b)
    {
        back->sibling=b;
        b=b->sibling;
        back=back->sibling;
        back->sibling=NULL;
    }
    return temp; 
} 
  
Node *H2union(Node *a,Node *b) 
{ 
    if (a==NULL&&b==NULL) 
    return NULL; 
  
    Node *temp=H2merge(a,b); 
    if(temp==NULL)
    return NULL;
    Node *prev=NULL;
    Node *cur=temp;
    Node *next=cur->sibling; 
    while(next) 
    { 
        if((next->sibling!=NULL)&&((next->sibling)->degree==cur->degree))
        { 
            prev=cur; 
            cur=next; 
        } 
        else if(cur->degree!=next->degree)
        {
            prev=cur; 
            cur=next; 
        }
        else
        { 
            if(cur->val<=next->val) 
            { 
                cur->sibling=next->sibling; 
                next->parent=cur; 
                next->sibling=cur->child; 
                cur->child=next; 
                cur->degree=cur->degree+1; 
            } 
            else
            { 
                if(prev==NULL) 
                temp=next; 
                else
                prev->sibling=next; 
                cur->parent=next; 
                cur->sibling=next->child; 
                next->child=cur; 
                next->degree=next->degree+1; 
                cur=next; 
            } 
        } 
        next=cur->sibling; 
    } 
    return temp; 
} 
  
void H2insert(long long int n,long long int v) 
{ 
    Node *temp=new Node; 
    temp->val=v; 
    temp->pos=n; 
    temp->parent=NULL; 
    temp->sibling=NULL; 
    temp->child=NULL; 
    temp->degree=0; 
    root=H2union(root,temp); 
} 

Node *H2findmin(Node *h)
{
    int min=999999;
    Node *temp=NULL;Node *cur=h;
    while(cur)
    {
        if(cur->val<min)
        {
            min=cur->val;
            temp=cur;
        }
        cur=cur->sibling;
    }
    return temp;
}
Node *H2extractmin(Node *h) 
{ 
    if (h==NULL) 
    return NULL; 
    Node *prev=NULL; 
    Node *min_node=h; 

    long long int min=h->val; 
    Node *cur=h; 
    while(cur->sibling!=NULL) 
    { 
        if((cur->sibling)->val<min) 
        { 
            min=(cur->sibling)->val; 
            prev=cur; 
            min_node=cur->sibling; 
        } 
        cur=cur->sibling; 
    } 
    if(prev==NULL&&min_node->sibling==NULL) 
    h=NULL;
    else if(prev==NULL) 
    h=min_node->sibling; 
    else
    prev->sibling=min_node->sibling; 
        
    Node *c=NULL;
    Node *temp1=NULL;
    Node *temp2=NULL;
    if(min_node->child!=NULL) 
    { 
        temp1=min_node->child;
        while(temp1)
        {
            temp2=temp1;
            temp1=temp1->sibling;
            temp2->sibling=c;
            c=temp2;
        }
        min_node->sibling=NULL;
        delete(min_node);
    } 
    return H2union(h,c); 
}  
//----------------------------
//fibonacci
struct node
{
    long long int val,pos,rank;
    node *parent;
    node *child;
    node *left;
    node *right;
} *minimum=NULL;
long long int fsize=0;
void H3insertnode(long long int v,long long int n)
{
    node *temp=new node;temp->rank=0;
    temp->val=v;temp->pos=n;
    temp->parent=NULL;
    temp->child=NULL;
    temp->left=temp;
    temp->right=temp;
    
    if(minimum!=NULL)
    {
        node *temp1=minimum;
        temp1=temp1->left;

            temp->right=minimum;
            temp1->right=temp;
            temp->left=temp1;
            minimum->left=temp;

        if(v<minimum->val)
        minimum=temp;
    }
    else
    {
        minimum=temp;
    }
    fsize++;
}
void H3consolidte()
{
    long int max=999999;
    node *arr[100000];
    for(int i=0;i<=fsize;i++)
    arr[i]=NULL;
    long int j=0;
    node *temp=minimum;
    while(j<fsize)
    {
        int r=temp->rank;
        if(arr[r]==NULL)
        {
            arr[r]=temp;
            temp=temp->right;
        }
        else
        {
            node *temp1=temp;
            temp=temp->right;
            while(arr[r])
            {
                if(arr[r]->val>temp1->val)
                {
                    node *s=arr[r];
                    arr[r]=temp1;
                    temp1=s;
                }
                node *t=arr[r];
                node *p1=t->child;
               if(p1==NULL)
               {
                   node *temp2=temp1->left;
                   node *temp3=temp1->right;
                   (temp2)->right=temp3;
                   (temp3)->left=temp2;
                   temp1->right=temp1;
                   temp1->left=temp1;
                   temp1->parent=t;
                   t->child=temp1;
               }
               else
               {
                   node *temp2=temp1->left;
                   node *temp3=temp1->right;
                   (temp2)->right=temp3;
                   (temp3)->left=temp2;
                   node *p2=p1->right;
                   node *p3=p1->left;
                   p2->left=temp1;
                   p1->right=temp1;
                   temp1->right=p2;
                   temp1->left=p3;
                   temp1->parent=t;
                   t->child=temp1;
               }
               temp1=arr[r];
               arr[r]=NULL;
               r++;
                
                if(temp1->val<max)
                {
                    minimum=temp1;
                    max=temp1->val;
                }
            }
            arr[temp1->rank]=temp1;
        }
        j++;
    }
}
void H3extractmin()
{
    if(minimum==NULL)
    return;
    node *temp=minimum;
    node *temp1=minimum->child;
    if(temp->child)
    {
        node *p=temp1;
        int f=0;
        while(f<=1)
        {
            if(p==temp1)
            f++;
            p->parent=NULL;
            p=p->right;
        }
        node *temp2=temp1->left;
        node *temp3=minimum->left;
        node *temp4=minimum->right;
        temp3->right=temp1;
        temp1->left=temp3;
        temp4->left=temp2;
        temp2->right=temp4;
        minimum=temp1;
        temp->child=NULL;
        delete(temp);
        node *ptr=temp1->right;
        while(ptr!=temp1)
        {
            if(ptr->val<minimum->val)
            minimum=ptr;
            ptr=ptr->right;
        }
        fsize--;
    }
    else
    {
        if(temp->left==temp&&temp->right==temp)
        {
            minimum=NULL;
            fsize--;
        }
        else
        {
            (temp->left)->right=temp->right;
            (temp->right)->left=temp->left;
            fsize--;
        }
    }
    if(fsize>1)
    H3consolidte();
}
//----------------------------
int bellman(long int n)
{
    int r=0;
    for(int i=1;i<=n;i++)
    dist[i]=999999;
    for(int i=1;i<=n;i++)
    {
        adjlist[0].pb({i,0});
    }
    queue<int> q;
    dist[r]=0;
    int find[100005]={0},check[100005]={0};
    find[r]=1;
    q.push(r);
    while(!q.empty())
    {
        int index;
        index=q.front();
        q.pop();
        find[index]=0;
        for(auto i=adjlist[index].begin();i!=adjlist[index].end();i++)
        {
            if(dist[index]+i->second<dist[i->first])
            {
                dist[i->first]=dist[index]+i->second;
                if(find[i->first]==0)
                {
                    q.push(i->first);
                    find[i->first]=1;
                    check[i->first]++;
                    if(check[i->first]>n+1)
                    return 1;
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(auto j=adj[i].begin();j!=adj[i].end();j++)
        {
            j->second+=dist[i]-dist[j->first];
        }
    }
    return 0;
}
//dijkstra implementation using binary heap
int H1dijkstra(long long int r,long long int n)
{
    memset(vis,0,sizeof(vis));
    m.clear();
    for(long int i=1;i<=n;i++)
    sp[r][i]=999999;

    H1insert(r,0);
    sp[r][r]=0;
    while(!H1empty())
    {
        pair<long long int,long long int> node=H1extractmin();
        long long int index,weight;
        weight=node.second;
        index=node.first;
        if(weight<0)
        return 1;
        for(auto i=adj[index].begin();i!=adj[index].end();i++)
        {
            if(i->second<0)
            return 1;
            if(weight+i->second<sp[r][i->first])
            {
                sp[r][i->first]=weight+i->second;
                if(vis[i->first]==0)
                H1insert(i->first,sp[r][i->first]);
                else
                H1decreasekey(i->first,sp[r][i->first]);
            }
        }
    }
    return 0;
}
//dijkstra implementation using binomial heap
int H2dijkstra(long long int r,long long int n)
{
    for(long int i=1;i<=n;i++)
    sp[r][i]=999999;

    H2insert(r,0);
    sp[r][r]=0;
    while(root!=NULL)
    {
        Node *node=H2findmin(root);
        long long int index,weight;
        weight=node->val;
        index=node->pos;
        root=H2extractmin(root);
        if(weight<0)
        return 1;
        for(auto i=adj[index].begin();i!=adj[index].end();i++)
        {
            if(i->second<0)
            return 1;
            if(weight+i->second<sp[r][i->first])
            {
                sp[r][i->first]=weight+i->second;
                H2insert(i->first,sp[r][i->first]);
            }
        }
    }
    return 0;
}
//dijkstra implementation uing fibonacci heap
int H3dijkstra(long long int r,long long int n)
{
    for(long int i=1;i<=n;i++)
    sp[r][i]=999999;

    H3insertnode(0,r);
    sp[r][r]=0;
    while(fsize>0)
    {
        node *q=minimum;
        long long int index,weight;
        weight=q->val;
        index=q->pos;
        H3extractmin();
        if(weight<0)
        return 1;
        for(auto i=adj[index].begin();i!=adj[index].end();i++)
        {
            if(i->second<0)
            return 1;
            if(weight+i->second<sp[r][i->first])
            {
                sp[r][i->first]=weight+i->second;
                H3insertnode(sp[r][i->first],i->first);
            }
        }
    }
    return 0;
}
//dijkstra implementation using array
vector<pair<long long int,long long int>> v;
int arr_dijkstra(long int r,int n)
{
    v.clear();
    for(int i=1;i<=n;i++)
    sp[r][i]=999999;

    v.pb({r,0});
    sp[r][r]=0;
    while(!v.empty())
    {
        long long int itr=0,min=999999;
        for(int i=0;i<v.size();i++)
        {
            if(v[i].second<min)
            {
                itr=i;
                min=v[i].second;
            }
        }
        long int index,weight;
        weight=v[itr].second;
        index=v[itr].first;
        v.erase(itr+v.begin());
        if(weight<0)
        return 1;
        for(auto i=adj[index].begin();i!=adj[index].end();i++)
        {
            if(i->second<0)
            return 1;
            if(weight+i->second<sp[r][i->first])
            {
                sp[r][i->first]=weight+i->second;
                v.pb({i->first,sp[r][i->first]});
            }
        }
    }
    return 0;
}
int main(int argc,char*argv[])
{
    vector<double> timetaken;
    long int t,n,d,w;
    cin>>t;
    while(t--)
    {root=NULL;minimum=NULL;fsize=0;memset(vis,0,sizeof(vis));
    clock_t time;
    time=clock();
    int ch=-1;
    if(argc!=1)
    {
        ch=atoi(argv[1]);
    }
        cin>>n>>d;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                cin>>w;
                if(i==j)
                continue;
                if(w!=999999)
                {
                    adj[i].pb({j,w});
                    adjlist[i].pb({j,w});
                }
                sp[i][j]=999999;
            }
        }
        long long int a=3;
        long long int flag=bellman(n);
        if(flag==1)
        cout<<-1<<endl;
        else
        {
            int f;
            for(int i=1;i<=n;i++)
            {
                if(argc==1||*argv[1]=='4')
                f=H3dijkstra(i,n);
                else if(*argv[1]=='1')
                f=arr_dijkstra(i,n);
                else if(*argv[1]=='2')
                f=H1dijkstra(i,n);
                else if(*argv[1]=='3')
                f=H2dijkstra(i,n);
                
                if(f==1)
                break;
                minimum=NULL;
            }
            if(f==1)
            cout<<-1<<endl;
            else
            {
                for(int i=1;i<=n;i++)
                {
                    for(int j=1;j<=n;j++)
                    {
                        if(sp[i][j]==999999)
                        cout<<sp[i][j]<<" ";
                        else
                        cout<<sp[i][j]-dist[i]+dist[j]<<" ";
                    }
                    cout<<endl;
                }
            }
        }
        for(int i=1;i<=n;i++)
        {
            adj[i].clear();
            adjlist[i].clear();
        }
        heap.clear();
        time=clock()-time;
        timetaken.pb(((double)t)/CLOCKS_PER_SEC);
    }
    for(auto i=timetaken.begin();i!=timetaken.end();i++)
    {
        cout<<*i<<" ";
    }
    
    return 0;
}
