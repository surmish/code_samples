/* Extract all leaf nodes from a Binary tree into a doubly linked list */

#include <algorithm>
/* #include <bitset> */
#include <climits>
/* #include <cmath> */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

class Node {
private:
  int32_t data;
  std::shared_ptr<Node> left_ptr, right_ptr;

public:
  void set_data(int32_t value) { data = value; }
  void set_left_ptr(std::shared_ptr<Node> node_ptr) {
    left_ptr = std::move(node_ptr);
  }
  void set_right_ptr(std::shared_ptr<Node> node_ptr) {
    right_ptr = std::move(node_ptr);
  }

  int32_t get_data() { return data; }
  std::shared_ptr<Node> get_left_ptr() { return left_ptr; }
  std::shared_ptr<Node> get_right_ptr() { return right_ptr; }

  Node() {
    data = 0;
    left_ptr = nullptr;
    right_ptr = nullptr;
  }
  explicit Node(int32_t value) {
    data = value;
    left_ptr = nullptr;
    right_ptr = nullptr;
  }
};

class BinaryTree {
private:
  std::shared_ptr<Node> root;

public:
  auto get_root() { return root; }
  BinaryTree() {
    /* std::cout << "Empty tree created!" << std::endl; */
    root = nullptr;
  }
  explicit BinaryTree(int32_t value) {
    /* std::cout << "Tree created with root value:" << value << std::endl; */
    root = std::make_shared<Node>();
    root->set_data(value);
    root->set_left_ptr(nullptr);
    root->set_left_ptr(nullptr);
  }
  void BinaryTreeInsert(int32_t value) {
    if (root == nullptr) {
      /* std::cout << "Root created with inserted value: " << value <<
       * std::endl; */
      root = std::make_shared<Node>();
      root->set_data(value);
      root->set_left_ptr(nullptr);
      root->set_right_ptr(nullptr);
      return;
    }
    std::shared_ptr<Node> current = root;
    std::shared_ptr<Node> newNode = std::make_shared<Node>(value);

    /* std::cout << "Values traversed: " << root->get_data() << ":"; */
    while (
        (current->get_left_ptr() != nullptr && current->get_data() > value) ||
        (current->get_right_ptr() != nullptr && current->get_data() <= value)) {
      if (current->get_data() > value) {
        current = current->get_left_ptr();
      } else {
        current = current->get_right_ptr();
      }
      /* std::cout << current->get_data() << ":"; */
    }
    /* std::cout << std::endl; */
    if (current->get_data() > value) {
      if (current->get_left_ptr() != nullptr) {
        /* std::cout << "ERROR! Left ptr should be null!!" << std::endl; */
        return;
      }
      current->set_left_ptr(newNode);
    } else {
      if (current->get_right_ptr() != nullptr) {
        /* std::cout << "ERROR! Left ptr should be null!!" << std::endl; */
        return;
      }
      current->set_right_ptr(newNode);
    }
    /* std::cout << newNode->get_data() << " inserted!!" << std::endl; */
  }
  void InOrderTraverse() {
    if (root == nullptr) {
      return;
    }
    std::stack<std::shared_ptr<Node>> nodeStack;
    auto current = root;
    while (current != nullptr || !nodeStack.empty()) {
      while (current != nullptr) {
        nodeStack.push(current);
        current = current->get_left_ptr();
      }
      current = nodeStack.top();
      std::cout << "IOTW val is: " << current->get_data() << std::endl;
      /* if (isLeaf(current)) { */
      /* std::cout << "Leaf val is: " << current->get_data() << std::endl; */
      /* } */
      nodeStack.pop();
      current = current->get_right_ptr();
    }
  }
};

class DoublyLinkedList {
private:
  std::shared_ptr<Node> head, tail;
  /* data */
public:
  DoublyLinkedList() { head = nullptr; }
  explicit DoublyLinkedList(std::shared_ptr<Node> node) {
    head = std::move(node);
  }
  bool isLeaf(const std::shared_ptr<Node> &node) {
    if (node == nullptr) {
      std::cout << "ERROR! isLeaf called for a nullptr" << std::endl;
    }
    return ((node->get_left_ptr() == nullptr) &&
            (node->get_right_ptr() == nullptr));
  }
  void InsertLeafNodesFromBinaryTree(BinaryTree T) {
    std::shared_ptr<Node> current = T.get_root();
    if (current == nullptr) {
      return;
    }

    std::stack<std::shared_ptr<Node>> nodeStack;
    while (current != nullptr || !nodeStack.empty()) {
      while (current != nullptr) {
        nodeStack.push(current);
        /* std::cout << "Value: " << current->get_data() << " pushed into stack"
         */
        /*           << std::endl; */
        if (current->get_left_ptr() != nullptr &&
            isLeaf(current->get_left_ptr())) {
          /* std::cout << "Value: " << current->get_left_ptr()->get_data() */
          /*           << " inserted into DLL" << std::endl; */
          InsertNode(current->get_left_ptr());
          current->set_left_ptr(nullptr);
        }
        current = current->get_left_ptr();
      }
      current = nodeStack.top();
      /* if (isLeaf(current)) { */
      /*   std::cout << "Leaf val is: " << current->get_data() << std::endl; */
      /* } */
      nodeStack.pop();
      if (current->get_right_ptr() != nullptr &&
          isLeaf(current->get_right_ptr())) {
        InsertNode(current->get_right_ptr());
        /* std::cout << "Value: " << current->get_right_ptr()->get_data() */
        /*           << " inserted into DLL" << std::endl; */
        current->set_right_ptr(nullptr);
      }
      current = current->get_right_ptr();
    }
  }
  void InsertNode(const std::shared_ptr<Node> &node) {
    if (node->get_left_ptr() != nullptr || node->get_right_ptr() != nullptr) {
      std::cout
          << "ERROR! Only leaf nodes from the Binary Tree can be inserted!."
          << std::endl;
      return;
    }
    if (tail != nullptr) {
      tail->set_right_ptr(node);
      node->set_left_ptr(tail);
      tail = node;
    } else {
      head = node;
      tail = node;
    }
  }
  void printDLL(std::ofstream &fout) {
    auto current = head;
    /* fout << "DLL is: " ; */
    while (current != nullptr) {
      fout << current->get_data() << std::endl;
      /* std::cout << current->get_data() << ":"; */
      current = current->get_right_ptr();
    }
  }
};

void insertIntoBST(BinaryTree &T, const std::vector<int32_t> &v, uint32_t p,
                   uint32_t r) {
  if (p < r) {
    uint32_t q = (p / 2) + (r / 2) + (p & r & 1u);
    /* std::cout << "middle value q inserted: " << q << std::endl; */
    T.BinaryTreeInsert(v[q]);
    if (p != (q - 1)) {
      insertIntoBST(T, v, p, q - 1);
    } else {
      /* std::cout << "left value p inserted: " << p << std::endl; */
      T.BinaryTreeInsert(v[p]);
    }
    if (r != (q + 1)) {
      insertIntoBST(T, v, q + 1, r);
    } else {
      /* std::cout << "right value r inserted: " << r << std::endl; */
      T.BinaryTreeInsert(v[r]);
    }
  }
};

int main(int argc, const char **argv) {
  std::ifstream fin(getenv("INPUT_PATH"), std::ios_base::in);
  std::ofstream fout(getenv("OUTPUT_PATH"), std::ios_base::out);

  uint32_t q;
  fin >> q;
  fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  BinaryTree T;

  for (uint32_t q_itr = 0; q_itr < q; q_itr++) {
    uint32_t n;
    fin >> n;
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    T.BinaryTreeInsert(n);
    /* fout << result << "\n"; */
  }
  /* T.InOrderTraverse(); */
  DoublyLinkedList DLL;
  DLL.InsertLeafNodesFromBinaryTree(T);
  DLL.printDLL(fout);

  /* std::vector<int32_t> vector_of_int; */
  /* uint32_t vector_size = 4095; */
  /* vector_of_int.reserve(vector_size); */
  /* for (uint32_t i = 0; i < vector_size; i++) { */
  /*   vector_of_int.push_back(i); */
  /* } */
  /* std::random_shuffle ( vector_of_int.begin(), vector_of_int.end() ); */
  /* for (auto elem : vector_of_int) { */
  /*   fout << elem << std::endl; */
  /* } */

  /* BinaryTree balancedBST; */
  /* DoublyLinkedList DLL_balancedBST; */
  /* insertIntoBST(balancedBST, vector_of_int, 0, vector_of_int.size() - 1); */
  /* /1* balancedBST.InOrderTraverse(); *1/ */
  /* DLL_balancedBST.InsertLeafNodesFromBinaryTree(balancedBST); */
  /* DLL_balancedBST.printDLL(fout); */

  fout.close();

  (void)argc;
  (void)argv;
  return 0;
}
