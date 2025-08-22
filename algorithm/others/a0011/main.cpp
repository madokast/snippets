#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

using node = pair<int, int>;

const int END = -1;

int main() {
    int number;
    cin >> number;

    vector<node> list;
    // important! otherwise, the vector will be reallocated
    // making the reference to the node invalid
    list.reserve(number); 
    unordered_map<int, int> loc(number);
    

    int head;
    cin >> head;
    list.emplace_back(head, END);
    int head_loc = 0;

    for (int i = 1; i < number; i++) {
        int insert_loc_by_value, new_value;
        cin >> new_value >> insert_loc_by_value;

        // get the previous
        int insert_loc = loc[insert_loc_by_value];
        node& insert_node = list[insert_loc];

        // new node at last
        int new_node_loc = list.size();
        list.emplace_back(new_value, insert_node.second);
        loc[new_value] = new_node_loc;

        // previous points to the new node
        insert_node.second = new_node_loc;
    }

    // for (auto &node : list) {
    //     cout << node.first << " at " << node.second << endl;
    // }
    

    int delete_value;
    cin >> delete_value;
    
    int current_loc = head_loc;
    while (current_loc != END) {
        node& current_node = list[current_loc];
        if (current_node.first != delete_value) {
            cout << current_node.first << " ";
        }
        current_loc = current_node.second;
    }
}
// 64 位输出请用 printf("%lld")