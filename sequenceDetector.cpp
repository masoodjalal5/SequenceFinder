#include <iostream>
#include <vector>	// Using vector cux they dynamic.
using namespace std;

class sequenceDetector {
	public:
		long seq;								// User defined Sequence
		long seqToFind;							// Sequnce that i need to match with, also user defined
		int counter = 0;						// counts the state changes only. shouldve named it to state_counter but too late.. is it.? maybe
		char presentState = 'A';
		
		vector<int> seq_vec {};					// Break the number into individual single digit values and store them.
		vector<int> seqToFind_vec {};			// Same thing for the comparison sequence
		vector<char> state {};					// Stores the states, the number of states is produced dynamically, it has the same size as the comparison seq
		
		// Constructor Yo.
		sequenceDetector (long seq, long seqToFind){
			this->seq = seq;
			this->seqToFind = seqToFind;
			
			state.push_back('A');
		}
		
		// Converts the numeric sequence to individual digits
		void get_vectored_seq(int input_seq, vector <int>& output_vec_seq){
			
			// segments the number to digits
			segment_seq(input_seq, output_vec_seq);
			
			// Reverses the sequence, should have used stack but i didnt want to put in the effort.
			int n = output_vec_seq.size();
			for (int i = 0; i < n/2; ++i)
				swap(output_vec_seq[i], output_vec_seq[n-i-1]);
			
			// display the vector, self explanatory
			display_vector(output_vec_seq);
		}
		
		// definition of the function which segments numeric number to digits. Recursive BTW, so be careful
		void segment_seq (int input_seq, vector <int>& output_vec_seq){
			
			// Stopping/Exit condition
			if (input_seq == 0)
				return;
				
			output_vec_seq.push_back(input_seq % 10);	// Vectors look good.
			
			segment_seq (input_seq / 10, output_vec_seq);	// recalling the function
		}
		
		// Displaying the vectors.
		void display_vector (vector<int>& output_vec_seq){
			
			for(int i = 0; i < output_vec_seq.size(); i++){
				
				cout << output_vec_seq.at(i) << " ";
			}
			cout << endl;
		}
		
		// Definition of State machine to handle the comparison matching.
		void sequenceFinder (){
			
			// Had to predefine the states, but there should be same number of states as the digits. So had to wait this far	
			fillState();
			
			// So it takes the numbers which user inserted, ie 1234345678
			// This loops runs the length of the sequence vector.
			for (int i = 0; i < seq_vec.size(); i++){
				
				// Does the heavy lifting, comparison etc, Also recursive so beware, also not hard to understand.
				checkNextInSeq(i, presentState);
				
				// Yay
				if (counter == seqToFind_vec.size()){
					cout << "Sequence Found | index : " << i << endl << endl;
					
					// Incase there are multiple intances of the same subsequence in the sequence
					presentState = 'A';
					counter = 0;
				}
				else {
//					cout << endl << "No match found." << endl;
				}
			}
			
//			Debugging Tools.
//			cout << endl << counter << " : " << seqToFind_vec.size() << endl;
//			
//			vector<char>::iterator iter;
//			for (iter = state.begin(); iter < state.end(); ++iter)
//				cout << *iter << " ";
//			cout << endl;
		}
		
		// Welcome to hell, the main comparison function which happens to be recursive, this is the definition.
		void checkNextInSeq (int next_idx, char presentState){
			
			// exit condition, when it runs through the whole of toFind vector.
			if (counter >= seqToFind_vec.size())
				return;
			
			// Genius Debugging here lol
			// cout << seq_vec.at(next_idx) << " : " << seqToFind_vec.at(counter) << endl;
			
			// The presentState contains the current state which is set as 'A', it is compared with the state that is stored
			// in location 0 of the state vector which is 'A' as well.
			// the next_idx is the index that goes through the original sequence, the conuter counts the sub sequence(aka the toFind sequence)
			// The state and seqToFind are similar and depend on counter which is only incremented when a match is found.
			// So the current state and the state at position should be equal and the sequence values must match for it to go into the if part.
			// Lets take 1232345678 as sequence and 2345 as sub sequence. At first iteration the left of AND is true, but the right of AND is false
			// as we are comparing 1 and 2, so no, it goes to the elese part. In the second iteration, the left side is True, and the right side is True
			// since we are comparing 2 and 2. So we go to the if part, change the state to B, increment the counter and then call the function again
			// Recursion baby. Now we go to 3rd iteration, the Left Side is True, but the Right side is true as well, comparing state B with B and 3 with 3
			// State change to C. Fourth iteration, left side is true, but right side isnt, we are now comparing 2 with 4. So we go to else statement, 
			// everything is reset (Remember the state changed to C, but since we were fooled and there was no complete sequence so we have to go to start.)
			// So now in the else we set the state to A, and counter to 0. Remember counter is linked to the subsequence which we are trying to match.
			// In the fifth iteration, left matches, right matches, increment state to B from A and life is good. 6th iteration, left true, right true,
			// increment state to C, life goes on. 7th iteration, left is true, right is true, state to D and counter +1, But now if you were paying attention
			// the counter is 4, which is the length of the sub sequence, so it goes to exit condition and hurray, youve done it. I hate recursion
			
			if (presentState == state.at(counter) && seq_vec.at(next_idx) == seqToFind_vec.at(counter)){
				
				cout << "Matched : Sequnce " << seq_vec.at(next_idx) << " | " << seqToFind_vec.at(counter)
					 << ": State Change Initiated ... \t CurrentState => " << presentState << endl;
				presentState += 1;
				counter += 1;
				
				// Recalling a team mate. 
				checkNextInSeq(next_idx+1, presentState);
			}
			else{
				// Reset the whole comparison if the seqeunce is not correct halfway.
				counter = 0;
				presentState = 'A';
//				cout << "Failed: Present State " << presentState << " : " << "Resetting..." << endl;
			}
		}
		// Fills the state vector with states.
		void fillState(){
			
			// first state is set to 'A', the rest are filled by incrementing the value of first location
			for (int i = 1; i < seqToFind_vec.size(); i++){
				state.push_back(state.at(0)+i);
			}
		}

};
int main(){
	
	long seq;
	long seqToFind;
	cout << "Enter a sequence:\t";
	cin >> seq;
	cout << "\nEnter a predefined sequence:\t";
	cin >> seqToFind;
	
	sequenceDetector findSeq(seq, seqToFind);
	findSeq.get_vectored_seq(findSeq.seq, findSeq.seq_vec);
	findSeq.get_vectored_seq(findSeq.seqToFind, findSeq.seqToFind_vec);
	findSeq.sequenceFinder();
	
	return 0;
}