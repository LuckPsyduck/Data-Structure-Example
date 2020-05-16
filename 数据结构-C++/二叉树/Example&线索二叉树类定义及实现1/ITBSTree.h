//派生类ITBSTree.h
template<class T>
class ITBSTree:public TBSTree<T>
{
private:
  //中序线索化二叉树
  void InThread(THNode<T> *&root,THNode<T> *&pre);

 public:
 
  ITBSTree(THNode<T> *&tree):TBSTree<T>(tree) {} //构造函数
  
//中序线索化二叉树
  void CreatInThread();

  //定位到中序下的第一个结点
  virtual THNode<T> *First();

  //将当前指针移到中序下的后继结点
  virtual void Next();

  //定位到中序下的最后一个结点
  virtual void Last();

  //将当前指针移到中序下的前驱结点
  virtual void Prior();

  //插入结点
  void InsertR(THNode<T> *&s,THNode<T> *&r);
};

template<class T>
void ITBSTree<T>::InThread(THNode<T> *&root,THNode<T> *&pre)
{
	if (root != NULL)
	{
		InThread(root->left, pre);//中序线索化左子树二叉树
		if (root->left == NULL)//当前结点左指针为空指针时
		{
			root->lflag = 1; //建立左线索指针
			root->left = pre;//建立左线索标志
		}
		if (pre->right == NULL)//前驱结点右指针为空指针时
		{
			pre->rflag = 1; //建立右线索标志
			pre->right = root;//建立右线索指针   //左树的最右端的后继为根结点
		}
		pre = root;//前驱结点右指针等于当前结点指针
		InThread(root->right, pre);
	}//中序线索化右子树二叉树
}

template<class T>
void ITBSTree<T>::CreatInThread()
{
	THNode<T> *t = root;//保存原根结点指针
	root = new THNode<T>;//建立头结点
	root->lflag = 0;
	root->rflag = 1;
	if (t == NULL)//当为空树时
	{
		root->left = root;
		root->right = root;
	}
	else     //当为非空树时
	{
		curr = root->left = t;//置头结点的左指针
		root->lflag = 0;    //置头结点的左标志
		THNode<T> *pre = root;//定义临时指针
		InThread(curr, pre);//中序线索化二叉树

		pre->right = root;//置最后一个结点的右线索//最后一个结点的后继指向根结点
		pre->rflag = 1;   //置最后一个结点的右标志

		root->right = pre;//置头结点的右线索
		root->rflag = 1;//置头结点的右标志
	}
}

template<class T>
THNode<T> *ITBSTree<T>::First()
{
	curr = root;//从根结点开始
	while (curr->lflag == 0)
		curr = curr->left;
	if (curr == root) 
		nextC = 1;//当二叉树为空时
	else 
		nextC = 0;//当二叉树为非空时
	return curr;
}

template<class T>
void ITBSTree<T>::Next()
{
	if (nextC == 1)
	{
		cerr << "已到二叉树尾!\n"; 
		exit(1);
	}
	THNode<T> *p = curr->right;//将当前指针移到中序下的后继结点
	if (curr->rflag == 0)
		while (p->lflag == 0)
			p = p->left;//找打右子树的最左端
	curr = p;
	if (curr == root)
		nextC = 1;
}

template<class T>
void ITBSTree<T>::Last()
{
	curr = root->right;//使curr定位到中序下的最后一个结点
	if (curr == root)
		priorC = 1;
	else 
		priorC = 0;
}

template<class T>
void ITBSTree<T>::Prior()
{
	if (priorC == 1)
	{
		cerr << "已到二叉树头!\n";
		exit(1);
	}
	THNode<T> *p = curr->left;
	if (curr->lflag == 0)
		while (p->rflag == 0)
			p = p->right;//左边的最右端
	curr = p;
	if (curr == root) 
		priorC = 1;
}

template<class T>
void ITBSTree<T>::InsertR(THNode<T> *&s,THNode<T> *&r)
{//将r当做s的右子女插入
	r->right = s->right;//s的右子女指针或后继线索传给r
	r->rflag = s->rflag;//传送标志
	r->left = s; 
	r->lflag = 1;//r的left成为指向s的前驱线索
	s->right = r; 
	s->rflag = 0;//r成为s的右子女
	if (r->rflag == 0)//s原来有右子女
	{
		curr = r->right;
		THNode<T> *temp = First();//在s原来的右子树中找中序下第一个结点
		temp->left = r;//建立指向r的前驱线索
	}//反正时刻记住中序遍历的情况
}