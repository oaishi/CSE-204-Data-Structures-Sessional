#include<stdio.h>
#include<stdlib.h>
#define FALSE_VALUE 0
#define TRUE_VALUE 1
int range;
struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
};



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==0)
        return 0;
    return getSize(node->right)+getSize(node->left)+1;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    int i=0;
    if(node == 0)
        return FALSE_VALUE;
    int j =node->item ;
    struct treeNode *temp = root;
    while(temp->item != j)
    {
        if(j>temp->item)
            temp=temp->right;
        else
            temp = temp->left;
        i++;
        if(temp== NULL)
            break;
    }
    return i;
}


int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here
    struct treeNode *temp = searchItem(root, item);
    if(temp)
        return calcNodeDepth(temp);
}

struct treeNode * parent (struct treeNode *root , int value)
{
    if(root->left == 0 && root->right == 0)
       return NULL;

    if( (root->left != 0 && root->left->item == value)|| (root->right != NULL && root->right->item == value))
       return root;

    if(root->item > value)
       return parent(root->left,value);

    if(root->item < value)
       return parent(root->right,value);
};

int deleteItem(struct treeNode * node, int item)
{
    //write your code here, return TRUE, FALSE
    struct treeNode* temp = root;
    struct treeNode* par;
    if(root == 0)
    {
        printf("ENTER VALUE FIRST !\n");
        return 0;
    }
    if(searchItem(root,item)==0)
        return 0;
    while(temp!=NULL)
    {
        if (temp==NULL)
            break;
        else if(item>temp->item)
            temp=temp->right;
        else if(item<temp->item)
            temp=temp->left;
        else if(item == temp->item)
        {
            if(temp->left==0 && temp->right==0)
            {
                if(temp == root)
                {
                    root=0;
                    free(temp);
                    return TRUE_VALUE;
                }
                par =parent(root,temp->item);
                if(par->left == temp)
                    par->left =0;
                else
                    par->right =0;
                free(temp);
                return TRUE_VALUE;
            }
            else if(temp->left == 0)
            {
                if(temp==root)
                {
                    root = root->right;
                    free(temp);
                    return TRUE_VALUE;
                }
                    par = parent(root,temp->item);
                    if(par->right==temp)
                        par->right = temp->right;
                    else
                        par->left = temp->right;
                    free(temp);
                    return TRUE_VALUE;
            }
            else if(temp->right == 0)
            {
                if(temp==root)
                {
                    root = root->left;
                    free(temp);
                    return TRUE_VALUE;
                }
                    par = parent(root,temp->item);
                    if(par->left==temp)
                        par->left = temp->left;
                    else
                        par->right = temp->left;
                    free(temp);
                    return TRUE_VALUE;
            }
            else if(temp->left && temp->right)
            {
                struct treeNode *chd = temp->right;
                if(chd->left!=0)
                    {
                while(chd->left!=0)
                {
                    // par = min;
                     chd=chd->left;
                }
                    }
                par = parent(root,chd->item);
                temp->item= chd->item;
                if(par->left == chd)
                    par->left =0;
                else if(par->right == chd)
                    par->right =0;
                free(chd);
                return TRUE_VALUE;
            }
            break;
        }
    }
    return FALSE_VALUE;
};


int getMinItem() //returns the minimum item in the tree
{
    //write your codes here
    struct treeNode *temp = root;
    if(temp == 0)
    {
        printf("Enter Element first\n");
        return FALSE_VALUE;
    }
    while(temp->left)
        temp=temp->left;
    return temp->item;
}

int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    struct treeNode *temp = root;
    if(temp == 0)
    {
        printf("Enter Element first\n");
        return FALSE_VALUE;
    }
    while(temp->right)
    {
        temp=temp->right;
    }
    return temp->item;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    //write your codes here
    if(root == 0)
        return FALSE_VALUE;
    if(leftBound == rightBound)
        return 1;
    if(node == root)
    {
        range =0;
    }
    if(node == 0 )
    {
        return range;
    }
    if(node->item >leftBound && node->item <rightBound)
    {
        rangeSearch(node->right,leftBound, rightBound);
        rangeSearch(node->left,leftBound,rightBound);
        range++;
        return range;
    }
    else if(node->item == leftBound)
    {
        range++;
        rangeSearch(node->right,leftBound, rightBound);
        return range;
    }
    else if(node->item == rightBound)
    {
        range++;
        rangeSearch(node->left,leftBound, rightBound);
        return range;
    }
    else
    {
        rangeSearch(node->left,leftBound, rightBound);
        rangeSearch(node->right,leftBound, rightBound);
    }
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0; i<height; i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. GETSIZe.\n");
        printf("8. Calculate depth of item. 9. DEPTH OF NODE.\n");
        printf("10. Get Minimum value. 11. Get Maximum value.\n");
        printf("12. Range. 13. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7)
        {
            printf("CURRENT SIZE : %d\n",getSize(root));
        }
        else if(ch==8)
        {
            int item;
            scanf("%d", &item);
            printf("Depth of %d = %d\n", item, calcDepth(item));
        }
        else if(ch==9)
        {
            struct treeNode *me;
            scanf("%d",&me);
            printf("Depth of %d = %d\n", me->item, calcNodeDepth(me));
        }
        else if(ch==10)
        {
            printf("Minterm = %d\n", getMinItem());
        }
        else if(ch==11)
        {
            printf("Maxterm = %d\n", getMaxItem());
        }
        else if(ch==12)
        {
            int l,r;
            printf("Enter THE small range :");
            scanf("%d", &l);
            printf("Enter THE large range :");
            scanf("%d", &r);
            printf("%d\n", rangeSearch(root,l,r));
        }
        else if(ch==13)
        {
            break;
        }
        else
            continue;
    }


}
