#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
/* Huffman树表示的事树中各结点的带权路径最小值
 * 采用顺序存储方式来表示Huffman树
 * 因为n个元素(叶子节点)，那么构造Huffman树的总节点个数为2n-1个
 * 数组的0号索引不使用，从1号索引开始存储元素，那么申请2n个
 * */
// Huffman树的节点结构（表中的一项）
typedef struct {
	int weight;				// 节点的权值
	int lChild, rChild;		// 指向孩子节点的索引号（数组下标）
	int parent;				// 存储该节点的父节点的索引号，0值表示该节点父节点不存在，他没有根节点
}HuffmanNode, *HuffmanTree;
// 构建Huffman树
HuffmanTree createHuffmanTree(const int *w, int n);
void releaseHuffmanTree(HuffmanTree tree);

typedef char *HuffmanCode;
// 依据Huffman树，产生n个字符的Huffman编码
HuffmanCode *createHuffmanCode(HuffmanTree tree, int n);
void releaseHuffmanCode(HuffmanCode *codes, int n);

#endif
