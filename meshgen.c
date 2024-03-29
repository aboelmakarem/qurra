// MeshGen
// Ahmed Hussein (amhussein4@gmail.com)
// March 28th 2024

#include "stdio.h"
#include "stdlib.h"
#include "tree.h"

void Do()
{
	Tree* tree = newTree();
	unsigned int max = 20000;
	for(unsigned i = 0 ; i < 2000000 ; ++i)
	{
		treeInsert(tree,rand() % max);
	}
	//treePrint(tree);
	if(isTreeValid(tree) == 0)
	{
		printf("valid tree\n");
	}
	else
	{
		printf("invalid tree\n");
	}
	printf("forward pass\n");
	TreeNode* snode = treeStart(tree);
	int prevKey = snode->key;
	unsigned int actualSize = 0;
	while(snode != NULL)
	{
		++actualSize;
		snode = nodeNext(snode);
		if(snode == NULL)
		{
			break;
		}
		if(snode->key <= prevKey)
		{
			printf("forward pass error\n");
		}
		prevKey = snode->key;
	}
	printf("forward actual size = %u\n",actualSize);
	actualSize = 0;
	printf("backward pass\n");
	TreeNode* enode = treeEnd(tree);
	prevKey = enode->key;
	while(enode != NULL)
	{
		++actualSize;
		enode = nodePrevious(enode);
		if(enode == NULL)
		{
			break;
		}
		if(enode->key >= prevKey)
		{
			printf("backward pass error\n");
		}
		prevKey = enode->key;
	}
	printf("backward actual size = %u\n",actualSize);
	// test tree find
	treeInsert(tree,43);
	treeInsert(tree,2756);
	treeInsert(tree,-27456);
	treeInsert(tree,42756);
	treeInsert(tree,-8136);
	treeInsert(tree,-3285);
	if(treeFind(tree,43) == NULL || (treeFind(tree,43)->key != 43))
	{
		printf("tree find error");
	}
	if(treeFind(tree,2756) == NULL || (treeFind(tree,2756)->key != 2756))
	{
		printf("tree find error");
	}
	if(treeFind(tree,-27456) == NULL || (treeFind(tree,-27456)->key != -27456))
	{
		printf("tree find error");
	}
	if(treeFind(tree,42756) == NULL || (treeFind(tree,42756)->key != 42756))
	{
		printf("tree find error");
	}
	if(treeFind(tree,-8136) == NULL || (treeFind(tree,-8136)->key != -8136))
	{
		printf("tree find error");
	}
	if(treeFind(tree,-3285) == NULL || (treeFind(tree,-3285)->key != -3285))
	{
		printf("tree find error");
	}
	if(treeFind(tree,max + 10) != NULL)
	{
		printf("tree find error");
	}
	freeTree(tree);
}

void readSTL(const char* filename)
{
	TreeNode n2;
	FILE* file = fopen(filename,"r");
	unsigned int readCount = 0;
	char cdata[80];
	readCount = fread(cdata,sizeof(char),80,file);
	if(readCount != 80)
	{
		printf("error: failed to read STL header\n");
		fclose(file);
		return;
	}
	unsigned int triCount = 0;
	readCount = fread(&triCount,sizeof(unsigned int),1,file);
	if(readCount != 1)
	{
		printf("error: failed to read STL triangle count\n");
		fclose(file);
		return;
	}
	float fdata[12];

	for(unsigned int i = 0 ; i < triCount ; ++i)
	{
		readCount = fread(fdata,sizeof(float),12,file);
		if(readCount != 12)
		{
			printf("error: failed to read triangle %u geometry\n",i);
			fclose(file);
			return;
		}
		// printf("tri %u: (%f,%f,%f) --> (%f,%f,%f) --> (%f,%f,%f) @ (%f,%f%f)\n",i,
		// 	fdata[0],fdata[1],fdata[2],
		// 	fdata[3],fdata[4],fdata[5],
		// 	fdata[6],fdata[7],fdata[8],
		// 	fdata[9],fdata[10],fdata[11]);
		readCount = fread(cdata,sizeof(char),2,file);
		if(readCount != 2)
		{
			printf("error: failed to read triangle %u attributes\n",i);
			fclose(file);
			return;
		}
	}
	fclose(file);
}

int main(int argc,char** argv)
{
	readSTL(argv[1]);
	Do();

	return 0;
}
