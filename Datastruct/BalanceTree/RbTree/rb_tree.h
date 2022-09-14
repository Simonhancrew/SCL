#pragma once
#include <iostream>

using namespace std;

// not tested version

#define RED 1
#define BLACK 2

typedef int KEY_TYPE;

// node define
struct rbtree_node {
  rbtree_node(KEY_TYPE key)
      : data(key),
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        color(BLACK),
        value(nullptr) {}
  KEY_TYPE data;
  void* value;
  // int hight;
  rbtree_node* left;
  rbtree_node* right;
  rbtree_node* parent;
  unsigned char color;
};

// rbtree
class rbtree {
 public:
  rbtree() : root(nullptr) {}

  // 插的时候先全红插，最后调整
  // 之前已经平衡了，不要去影响黑高
  // 只有在其父节点是红色的时候，违背了原则4的时候才需要调整
  void insert(KEY_TYPE key) {
    auto x = new rbtree_node(key);
    auto cur = root;
    rbtree_node* pre = nullptr;
    while (cur != nullptr) {
      pre = cur;
      if (x->data < cur->data) {
        cur = cur->left;
      } else if (x->data > cur->data) {
        cur = cur->right;
      } else {
        // 存在
        return;
      }
    }

    x->parent = pre;
    if (pre == nullptr) {
      root = x;
    } else if (x->data < pre->data) {
      pre->left = x;
    } else {
      pre->right = x;
    }

    x->left = nullptr;
    x->right = nullptr;
    x->color = RED;

    insert_fix(x);
  }

  // 父节点是红色才需要调整,当前节点永远是红色的。
  void insert_fix(rbtree_node* node) {
    // node->red
    while (node->parent->color == RED) {
      // 第一种情况，父节点是祖父的左儿子
      if (node->parent == node->parent->parent->left) {
        auto uncle = node->parent->parent->right;
        if (uncle && uncle->color == RED) {  // 叔叔是红色的,比较简单
          // 因为没有影响高度，祖父的两个儿子变黑，祖父变红就可以了。
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          // 往上走
          node = node->parent->parent;
        } else {  // 叔叔是黑色的
          if (node == node->parent->right) {
            node = node->parent;
            left_rotate(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          right_rotate(node->parent->parent);
        }
      } else {  // node的父节点是祖父节点的右儿子
        auto uncle = node->parent->parent->left;
        if (uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;

          node = node->parent->parent;
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            right_rotate(node);
          }

          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          left_rotate(node->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  rbtree_node* mini(rbtree_node* x) {
    while (x->left != nullptr) {
      x = x->left;
    }
    return x;
  }

  rbtree_node* successor(rbtree_node* x) {
    auto y = x->parent;
    if (x->right != nullptr) {
      return mini(x->right);
    }

    while (y != nullptr && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  rbtree_node* remove(rbtree_node* z) {
    rbtree_node* y = nullptr;
    rbtree_node* x = nullptr;
    if (z->left == nullptr || z->right == nullptr) {
      y = z;
    } else {
      y = successor(z);
    }

    if (y->left != nullptr) {
      x = y->left;
    } else if (y->right != nullptr) {
      x = y->right;
    }

    x->parent = y->parent;
    if (y->parent == nullptr) {
      root = x;
    } else if (y == y->parent->left) {
      y->parent->left = x;
    } else {
      y->parent->right = x;
    }

    if (y != z) {
      z->data = y->data;
      z->value = y->value;
    }

    if (y->color == BLACK) {
      remove_fix(x);
    }
    return y;
  }

  void remove_fix(rbtree_node* x) {
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        auto w = x->parent->right;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          left_rotate(x->parent);
          w = w->parent->right;
        }

        if (w->left->color == BLACK && w->right->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else {
          if (w->right->color == BLACK) {
            w->left->color = BLACK;
            w->color = RED;
            right_rotate(w);
            w = x->parent->right;
          }

          w->color = x->parent->color;
          w->parent->color = BLACK;
          w->right->color = BLACK;
          left_rotate(x->parent);
          x = root;
        }
      } else {
        auto w = x->parent->left;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          right_rotate(x->parent);
          w = x->parent->left;
        }

        if (w->left->color == BLACK && w->right->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else {
          if (w->left->color == BLACK) {
            w->right->color = BLACK;
            w->color = RED;
            left_rotate(w);
            w = w->parent->left;
          }

          w->color = x->parent->color;
          w->parent->color = BLACK;
          w->left->color = BLACK;
          right_rotate(x->parent);
          x = root;
        }
      }
    }
    x->color = BLACK;
  }

  void traverse(rbtree_node* node) {
    if (node != nullptr) {
      traverse(node->left);
      printf("key:%d,color:%d\n", node->data, node->color);
      traverse(node->right);
    }
  }

  rbtree_node* search(KEY_TYPE key) {
    auto node = root;
    while (node != nullptr) {
      if (key < node->data) {
        node = node->left;
      } else if (key > node->data) {
        node = node->right;
      } else {
        return node;
      }
    }
    return nullptr;
  }

  void left_rotate(rbtree_node* x) {
    auto y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void right_rotate(rbtree_node* y) {
    auto x = y->left;
    if (x->right != nullptr) {
      x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
      root = x;
    } else if (y == y->parent->left) {
      y->parent->left = x;
    } else {
      y->parent->left = x;
    }
  }

 private:
  rbtree_node* root;
};