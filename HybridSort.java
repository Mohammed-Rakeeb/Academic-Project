package cpsc331.assignment3;

import java.util.ArrayList;

/**
*
* Provides a hybrid algorithm to sort the elements of an array based on
* Merge Sort.
*
*/

public class HybridSort<T extends Comparable<T>> {

  // Data Fields

  private final int THRESHOLD;

  /**
  *
  * Constructs a hybrid sorting algorithm, based on Merge Sort, using
  * a default value (4) for the threshold.
  *
  */

  public HybridSort() {

    THRESHOLD = 4;

  }

  /**
  *
  * Constructs a hybrid sorting algorithm, based on Merge sort, using
  * an input value for the threshold.
  *
  * @param threshold the value to be used as threshold
  * @throws IllegalArgumentException if the input value is less than or
  *   equal to zero
  *
  */

  public HybridSort(int threshold) throws IllegalArgumentException {

    if (threshold >= 1) {

      THRESHOLD = threshold;

    } else {

      throw new IllegalArgumentException("The input threshold"
                                              + " must be positive.");

    }

  }

  /**
  *
  * Sorts an input ArrayList; does not copy in place.
  *
  * @param A the ArrayList to be sorted
  * @return an ArrayList with the same type and length of A, whose elements
  *   are those of&nbsp;A, reordered in non-decreasing order<br><br>
  *
  * Precondition:<br>
  * <ol style="list-style-type: lower-alpha">
  * <li> An ArrayList&nbsp;A, whose entries are non-null value of
  *      type&nbsp;T, is given as input.
  * </li>
  * </ol>
  * Postcondition:<br>
  * <ol style="list-style-type: lower-alpha">
  * <li> A ArrayList with the same type and length of&nbsp;A is returned as
  *      output. The entries of the output ArrayList are the entries
  *      of&nbsp;A, reordered (with multiplicities preserved) in
  *      non-decreasing order.
  * </li>
  * </ol>
  *
  */

  public ArrayList<T> sort(ArrayList<T> A) {

   if(A.size() <= THRESHOLD){
     ArrayList<T> B = copy(A);
     insertionSort(B);
     return B;
   }else{
     ArrayList<T> B1 = new ArrayList<T>();
     ArrayList<T> B2 = new ArrayList<T>();
     split(A, B1,B2);
     ArrayList<T> C1 = sort(B1);
     ArrayList<T> C2 = sort(B2);
     return merge(C1,C2);
   }


  }

  //
  // Returns a copy of an input ArrayList
  //
  // Precondition:
  // a) An ArrayList A with positive length, whose entries are non-null
  //    values with type T, is given as input.
  // Postcondition:
  // a) An ArrayList with the same type, length and contents of A (so that
  //    the entry in position j of this ArrayList is the same as the
  //    as the entry in position j of A, for 0 <= j <= A.size()-1) is
  //    returned as output.

  private ArrayList<T> copy(ArrayList<T> A) {

    ArrayList<T> B = new ArrayList<T>();

    for(int i =0 ;i < A.size() ;i++){
      B.add(A.get(i));
    }
    return B;

  }

  //
  // Sorts an input ArrayList in place
  //
  // Precondition:
  // a) An ArrayList B with positive size, whose entries are non-null
  //    values with type T, is given as input.
  // Postcondition:
  // b) The entries of B have been reordered, but otherwise unchanged,
  //    so that they are listed in nondecreasing order.

  private void insertionSort(ArrayList<T> B) {
    if(B.size() > 1){
      for (int i = 1 ; i < B.size(); i++) {
    	  T temp = B.get(i);
    	  int j = i - 1 ;
    	  while( (j>=0) && (B.get(j).compareTo(temp) > 0)) {
    		  B.set(j+1,B.get(j));
    		  j--;
         }
         B.set(j+1,temp) ;
       }
     }
   }


  // Splits an input ArrayList into a pair with approximately the same size
  //
  // Precondition:
  // a) An ArrayList A with size greater than or equal to two, whose
  //    entries are non-null values with type T, is given as a first input.
  //    A pair of ArrayLists B1 and B2, the each store values with type T
  //    but that both initially have size zero, are given as the second
  //    and third inputs.
  // b) The input array A has not changed. If it has size "length" then
  //    the sizes of B1 and B2 are the ceiling and floor of length/2,
  //    respectively. For 0 <= h <= ceil(length/2)-1, the entry in
  //    position h of B1 is equal to the entry in position h of A. For
  //    ceil(length/2) <= h <= length-1, the entry in position
  //    h - ceil(length/2) of B2 is equal to the entry in position h of A.

  private void split(ArrayList<T> A, ArrayList<T> B1, ArrayList<T> B2) {
    if( A.size() % 2 ==0 ){
      for ( int i = 0 ; i < A.size()/2 ; i++){
        B1.add(A.get(i));
      }
      for(int i = (A.size()/2 ) ; i < A.size() ; i++ ){
        B2.add(A.get(i));
      }
      }else{
      for( int i = 0; i <  (A.size() /2 + 1) ; i++ ){
    	  B1.add(A.get(i));
      }
      for( int i = (A.size() /2 + 1) ; i < A.size(); i++ ){
        B2.add(A.get(i));
      }
    }

  }

  // Merges a pair of sorted input ArrayLists.
  //
  // Precondition:
  // a) C1 is an ArrayList with positive size storing non-null elements000
  //    from an ordered type T that is sorted in non-decreasing order -
  //    so that for every integer h such that 0 <= h <= C1.size()-2,
  //    C1.get(h) <= C1.get(h+1).
  // b) C2 is an ArrayList with positive size storing non-null elements
  //    from an ordered type T that is sorted in non-decreasing order -
  //    so that for every integer h such that 0 <= h <= C2.size()-2,
  //    C2.get(h) <= C2.get(h+1).
  // Postcondition:
  // a) An ArrayList D, storing non-null values from the ordered type T,
  //    such that D.zize() = C1.size() + C2.size(), is returned as output.
  //    The entries stored in D are the entries stored in C1 and in C2
  //    (with multiplicities preserved), rearranged in non-decreasing order
  //    - so that for every integer h such that 0 <= h <= D.size()-2,
  //    D.get(h) <= D.get(h+1)

  private ArrayList<T> merge(ArrayList<T> C1, ArrayList<T> C2) {
    ArrayList<T> D = new ArrayList<T>();

    int index = 0;
		int p1 = 0;
		int p2 = 0;
		int n1 = C1.size();
		int n2 = C2.size();

		while( p1<n1 && p2<n2){
			if( C1.get(p1).compareTo(C2.get(p2))<0){
				D.add(index,C1.get(p1));
				index++;
				p1++;
			}else{
				D.add(index,C2.get(p2));
				index++;
				p2++;
			}
			if(p1==n1 && p2 < n2){
				for(int i = p2 ; i < n2 ; i++){
					D.add(index,C2.get(p2));
					index++;
					p2++;
				}
			}
			else if ( p2==n2 && p1 < n1){
				for(int i = p1 ; i < n1 ; i++){
					D.add(index,C1.get(p1));
					index++;
					p1++;
				}
			}
		}

		return D;

  }

}
