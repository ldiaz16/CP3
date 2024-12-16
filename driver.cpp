#include <iostream>
#include <string>
#include <cassert>
#include <random>
#include "FireLL.h"
#include "Voter.h"
using namespace std;


void test_isEmpty();
void test_iterator();
void test_add_left_and_add_right();
void test_makeEmpty();
void test_may_contain_dups();
void test_ordered();
void test_sort();
void test_remove_dups();
void test_import();



int count_FireLL(FireLL<Voter>& fll){

    /*
        This function counts your FireLL.
        It assumes that the iterator functionalities are correctly implemented.  
        * Please note that graders will use this function to test your iterator implementation,
        and also utilize it for grading other functionalities.                
    */
   fll.restart();
   Voter vt;
   int cnt = 0;
   while (!fll.done()) {
      vt = fll.go_to_next();
      cnt++;
   }
   return cnt;
}


int print_FireLL(FireLL<Voter>& fll){

    /*
        This is a helper function that prints your FireLL, which you may use for verification purposes.  
        It assumes that the iterator functionalities are correctly implemented.  
        Note that graders might refer to its output for grading.           

        If you encounter compilation errors related to `operator<<`, 
        add the following friend function to overload it for the `Voter` object:

                friend std::ostream& operator<<(std::ostream& os, const Voter& vt){
                    os << "First: "<< vt.first <<  ", Last: " << vt.last << ", Age: " << vt.age;
                    return os; 
    */

   fll.restart();
   Voter vt;
   int cnt = 0;
   while (!fll.done()) {
      vt = fll.go_to_next();
      cout << "[" << vt << "]" ;
      cnt++;
   }
   cout << endl;
   cout << "- FireLL count: " << cnt << endl;
   cout << endl;
   return cnt;
}

int main() {

    // Guideline to use the following test cases:
    //  1.If you have any other test code/main function comment it out.
    //  2.Use this main function.
    //  3.Make sure to include appropriate header files.
    //  4.You may need to make changes in the make file.
    

    cout << "Testing FireLL functionalities...\n";

    test_isEmpty();
    test_iterator();
    test_add_left_and_add_right();
    test_makeEmpty();
    test_may_contain_dups();
    test_ordered();

    test_sort();
    test_remove_dups();
    test_import();

    cout << "All tests completed.\n";
    return 0;
}


void test_isEmpty() {
    FireLL<Voter> list;
    cout << "Testing isEmpty: " << (list.isEmpty() ? "Pass" : "Fail") << "\n";
}

void test_iterator() {

    FireLL<Voter> list;
    int num_nodes = 28;
    for (int i = 0; i < num_nodes; ++i) {
        Voter voter = Voter("f-"+std::to_string(i), "l-"+std::to_string(i), i);
        list.add_right(voter, false);
    }
    cout << "Testing iterator: " << ( count_FireLL(list) == num_nodes ? "Pass" : "Fail") << "\n";
}



void test_add_left_and_add_right() {
    FireLL<Voter> list;

    for (int i = 0; i < 10; ++i) {
        Voter voter = Voter( "f-"+std::to_string(i), "l-"+std::to_string(i), i);
        list.add_right(voter, false);
    }

    for (int i = 9; i >= 0; i--) {
        Voter voter = Voter( "f-"+std::to_string(i), "l-"+std::to_string(i), i);
        list.add_left(voter, false);
    }

    // print_FireLL(list);
    int list_cnt = count_FireLL(list);
    cout << "Testing add_left and add_right: " << ( (!list.isEmpty() && list_cnt == 20) ? "Pass" : "Fail") << "\n";
    // cout << "Testing add_left and add_right: " << ( (!list.isEmpty()) ? "Pass" : "Fail") << "\n";
}

void test_makeEmpty() {
    FireLL<Voter> list;
    for (unsigned int i = 0; i < 100; ++i) {
        // Voter voter = Voter{ string{static_cast<char>('A' + i)}, string{static_cast<char>('A' + i + 1)}, i};
        Voter voter = Voter( "f-"+std::to_string(i), "l-"+std::to_string(i), i);
        list.add_right(voter, false);
    }

    int list_cnt_before = count_FireLL(list);
    // print_FireLL(list);

    list.makeEmpty();
    int list_cnt_after = count_FireLL(list);
    // print_FireLL(list);
    cout << "Testing makeEmpty: " << (list.isEmpty() && (list_cnt_before - list_cnt_after == 100)  ? "Pass" : "Fail") << "\n";
}



void test_may_contain_dups() {
    FireLL<Voter> list;
    Voter voter_1 = Voter("f-1", "l-1", 25);
    Voter voter_2 = Voter("f-2", "l-2", 21);

    cout << "Testing may_contain_dups: " << endl;
    list.add_right( voter_1, false);
    cout << "> subtest-1: " << (!list.may_contain_dups() ? "Pass" : "Fail") << "\n";
    list.add_right( voter_2, false);
    cout << "> subtest-2: " << (list.may_contain_dups() ? "Pass" : "Fail") << "\n";
    list.add_right( voter_1, false);
    cout << "> subtest-3: " << (list.may_contain_dups() ? "Pass" : "Fail") << "\n";
    list.remove_dups();
    cout << "> subtest-4: " << ( !list.may_contain_dups() ? "Pass" : "Fail") << "\n";
 

}


void test_ordered() {
    FireLL<Voter> list;
    Voter voter_1 = Voter("f-1", "l-1", 21);
    Voter voter_2 = Voter("f-3", "l-3", 25);
    Voter voter_0 = Voter("f-2", "l-2", 23);


    cout << "Testing ordered: " << endl;
    list.add_right( voter_1, false);
    cout << "> subtest-1: " << ( list.ordered() ? "Pass" : "Fail") << "\n";
    list.add_right( voter_2, false);
    cout << "> subtest-2: " << ( !list.ordered() ? "Pass" : "Fail") << "\n";
    list.add_right( voter_0, false);
    cout << "> subtest-3: " << ( !list.ordered() ? "Pass" : "Fail") << "\n";
    list.sort();
    cout << "> subtest-4: " << ( list.ordered() ? "Pass" : "Fail") << "\n";
 

}

void test_sort() {
    FireLL<Voter> unordered_list;
    FireLL<Voter> ordered_list;

    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 1000);

    for (int i = 0; i < 50; ++i) {
        int k = dist(gen);
        Voter voter = Voter( "f-"+std::to_string(k), "l-"+std::to_string(k), k);
        unordered_list.add_right(voter, true);
    }
    // print_FireLL( unordered_list  );

    for (int i = 0; i < 26; ++i) {
        Voter voter = Voter("f-" + std::string(1, 'a' + i), "l-" + std::string(1, 'a' + i), i);
        ordered_list.add_right(voter, true);
    }
    // print_FireLL( ordered_list  );    


    cout << "Testing sort"; 
    // print_FireLL( unordered_list  );
    int swaps = unordered_list.sort(); // check if swaps != 0
    // print_FireLL( unordered_list  );
    unordered_list.restart();
    Voter vt;
    Voter prev_vt;

    vt = unordered_list.go_to_next();
    bool failed = false;
    while (!unordered_list.done()) {
        prev_vt = vt;
        vt = unordered_list.go_to_next();
        //     cout << "prev_vt: " <<  prev_vt << "| vt: " << vt << endl;
        if (!(prev_vt < vt)){
            cout << "Testing sort: " << "Fail" << "\n";
            failed = true;
            break;
        }
    }
    cout << "Testing sort and swap count (unordered list): " << (swaps > 0 && unordered_list.ordered() && (failed == false) ? "Pass" : "Fail") << "\n";

    swaps = ordered_list.sort(); 
    cout << "Testing sort and swap count (ordered list): " << (swaps == 0 && ordered_list.ordered() ? "Pass" : "Fail") << "\n";

}

void test_remove_dups() {

    FireLL<Voter> list;
    for (int i = 0; i < 10; ++i) {
        Voter voter = Voter( "f-"+std::to_string(i), "l-"+std::to_string(i), i);
        list.add_right(voter, false);
    }
    for (int i = 9; i >= 0; i--) {
        Voter voter = Voter( "f-"+std::to_string(i), "l-"+std::to_string(i), i);
        list.add_left(voter, false);
    }
    list.remove_dups();
    // print_FireLL(list);
    int list_cnt = count_FireLL(list);
    cout << "Testing remove_dups: " << ( ( list_cnt == 10) && !list.may_contain_dups()  ? "Pass" : "Fail") << "\n";


}

void test_import() {
    // FireLL<Voter> list1, list2;

    cout << "Testing import: " << endl;
    FireLL<Voter> list1, list2, list3, list4;


    // If no_dups is true, the function should not add any item that matches one already in the list. If no_dups is false, no such check should be made.
        // list1 { a , b, c }
        // list2 { c , d, e }
    Voter voter_a = Voter( "f-a", "l-a", 1);
    Voter voter_b = Voter( "f-b", "l-b", 2);
    Voter voter_c = Voter( "f-c", "l-c", 3);
    Voter voter_d = Voter( "f-d", "l-d", 4);
    Voter voter_e = Voter( "f-e", "l-e", 5);

    list1.add_right( voter_a , false );
    list1.add_right( voter_b , false );
    list1.add_right( voter_c , false );
    
    list2.add_right( voter_c , false );
    list2.add_right( voter_d , false );
    list2.add_right( voter_e , false );

    list1.import(list2, true, false);
    int list_cnt = count_FireLL(list1);
    cout << "> subtest-1 : " << ( ( list_cnt == 5)  ? "Pass" : "Fail") << "\n";


    // If maintain_order is true and the list is currently in order, then the items should be added to maintain order in the list. 
    // If maintain_order is false, then the items should be added to the right side of the list.
        // list1 { a , c, e }
        // list2 { b , d }


    list3.add_right( voter_a , false );
    list3.add_right( voter_c , false );
    list3.add_right( voter_e , false );
    
    list4.add_right( voter_b , false );
    list4.add_right( voter_d , false );

    list3.import( list4, false, true );

    Voter prev_vt;
    Voter vt;
    list3.restart();
    vt = list3.go_to_next();
    bool failed = false;
    while (!list3.done()) {
        prev_vt = vt;
        vt = list3.go_to_next();
        // cout << "prev_vt: " <<  prev_vt << "| vt: " << vt << endl;        
        if (!(prev_vt < vt)){
            cout << "Testing sort: " << "Fail" << "\n";
            failed = true;
            break;
        }
    }
    cout << "> subtest-2 : " << ( !failed && list3.ordered()  ? "Pass" : "Fail" ) << "\n";

}