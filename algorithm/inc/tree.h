#ifndef __ALG_TREE_H__
#define __ALG_TREE_H__
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
	typedef int TreeElemTYpe;

	typedef struct TreeNode {
		struct TreeNode* parent;
		struct TreeNode* leftchild;
		struct TreeNode* nextRightSib;
		TreeElemTYpe elem;
	}TreeNode;

	typedef int BTreeElemType;

	typedef struct BTreeNode 
	{
		struct BTreeNode* paret;
		struct BTreeNode* lchild;
		struct BTreeNode* rchild;
		BTreeElemType elem;
	}BTreeNode;

#ifdef __cplusplus
}
#endif

#endif /*__ALG_TREE_H__*/
