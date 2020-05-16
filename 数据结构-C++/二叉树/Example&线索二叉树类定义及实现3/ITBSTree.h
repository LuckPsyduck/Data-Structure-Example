//派生类ITBSTree2.h

template<class T>
class ITBSTree:public TBSTree<T>
{
private:
  //中序线索化二叉树
  void InThread(THNode<T> *&root,THNode<T> *&pre);

public:
  //构造函数
  ITBSTree(THNode<T> *&tree):TBSTree<T>(tree) {}

  //中序线索化二叉树
  void CreatInThread();

  //线索二叉树的中序正向遍历
  virtual void First();

  //线索二叉树的中序反向遍历
  virtual void Last();
};

template<class T>
void ITBSTree<T>::InThread(THNode<T> *&root,THNode<T> *&pre)
{
	if (root != NULL)
	{
		InThread(root->left, pre);	//中序线索化左子树二叉树
		if (root->left == NULL)		//当前结点左指针为空指针时
		{
			root->lflag = 1;		//建立左线索指针
			root->left = pre;		//建立左线索标志
		}
		if (pre->right == NULL)//前驱结点右指针为空指针时
		{
			pre->rflag = 1; //建立右线索标志
			pre->right = root;//建立右线索指针
		}

		pre = root;//前驱结点右指针等于当前结点指针

		InThread(root->right, pre);//中序线索化右子树二叉树
	}
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
		curr = root->left = t;	//置头结点的左指针
		root->lflag = 0;		//置头结点的左标志
		THNode<T> *pre = root;	//定义临时指针
		InThread(curr, pre);	//中序线索化二叉树
															//相互变换
		pre->right = root;		//置最后一个结点的右线索
		pre->rflag = 1;			//置最后一个结点的右标志
		root->right = pre;		//置头结点的右线索
		root->rflag = 1;		//置头结点的右标志
	}
}

template<class T>
void ITBSTree<T>::First()
{
	THNode<T> *p;
	curr = root;			//从根结点开始
	while (curr->lflag == 0)
		curr = curr->left;
	if (curr == root)
		nextC = 1;//当二叉树为空时
	else 
		nextC = 0;//当二叉树为非空时

	while (nextC == 0)
	{
		cout << curr->data << "  ";
		p = curr->right;				//将当前指针移到中序下的后继结点
		if (curr->rflag == 0)
			while (p->lflag == 0)
				p = p->left;//最左边
		curr = p;
		if (curr == root) 
			nextC = 1;//空为1
	}
}

template<class T>
void ITBSTree<T>::Last()
{
	THNode<T> *p;
	curr = root->right;//使curr定位到中序下的最后一个结点
	if (curr == root)
		priorC = 1;
	else
		priorC = 0;

	while (priorC == 0)//右中左
	{
		cout << curr->data << "  ";
		p = curr->left;
		if (curr->lflag == 0)
			while (p->rflag == 0)
				p = p->right;
		curr = p;
		if (curr == root) 
			priorC = 1;
	}
}


