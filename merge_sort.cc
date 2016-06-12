// A test program to implement merge sort.

#include <iostream>
#include <random>

using namespace std;


// merge two sorted (ascending) arrays.
void
merge(int* a, unsigned int a_len,
      int* b, unsigned int b_len,
      int* r)
{
	int i, j;

	if ((a == 0) && (b == 0)) { return; }
	if (r == 0) { return; }

	if (a == 0) {
		for (i = 0; i < b_len; i++) {
			*r = *b;
			r++;
			b++;
		}
		return;
	}

	if (b == 0) {
		for (i = 0; i < a_len; i++) {
			*r = *a;
			r++;
			a++;
		}
		return;
	}

	i = j = 0;

	while ((i < a_len) && (j < b_len)) {
		if (*a <= *b) {
			*r = *a;
			r++;
			a++;
			i++;
		} else {
			*r = *b;
			r++;
			b++;
			j++;
		}
	}

	// if any left-over, pick up.
	while (i < a_len) {
		*r = *a;
		r++;
		a++;
		i++;
	}
	while (j < b_len) {
		*r = *b;
		r++;
		b++;
		j++;
	}
}

void
swap_int_p (int** pp1, int** pp2)
{
	int* temp = *pp1;
	*pp1 = *pp2;
	*pp2 = temp;
}

void
merge_sort (int* ar, unsigned int len)
{
	if ((ar == 0) || (len <= 1)) { return; } 

	// We can not do merge in place, so this is a same size array.
	int* temp = (int*)malloc(len * sizeof(int));	

	// start with 1, then 2, 4, 8, 16 etc.
	int c_size = 1;

	int* src; // current src.
	int* target; // current target.

	// Markers for the loop.
	int i1, i2, i3;
	
	// normally being c_size, but could be less for the end sessions.
	unsigned int l1, l2;

	src = temp;
	target = ar;

	while (c_size < len) {
		// idea is to merge back and forth
		// between 2 arrays.
		// - src and target alters each time.
		// - c_size double each time.
		swap_int_p (&src, &target);

		i1 = 0; 
		l1 = c_size;
		i2 = i1 + l1; 
		l2 = c_size;
		if ((c_size * 2) >= len) {
			l2 = len - l1;
		}
		i3 = 0;

		while (1) {
			// do the merge.
			merge(&(src[i1]),
			      l1, 
			      ((i2 >= 0)? &(src[i2]):0),
			      l2,
			      &(target[i3])); 


			// move forward.
			i1 += (l1 + l2);
			i3 += (l1 + l2);

			if (i1 >= len) {
				break;
			}
			if ((i1 + l1) >= len) {
				l1 = len - i1;
				i2 = -1; // use -1 to stop
				l2 = 0;
			} else {
				i2 += (l1 + l2);
				if ((i2 + l2) >= len) {
					l2 =  len - i2;
				}
			}
		}
		c_size = c_size * 2;
	}

	// If the final result happened not be in ar,
	// we need to copy them over.
	if (target != ar) {
		for (int k = 0; k < len; k++) {
			ar[k]  = target[k];
		}
	}
	free(temp);
}

void
print_array (int* a, unsigned int len)
{
	for (int i = 0; i < len; i++) {
		if ((i % 10) == 9) {
			std::cout << " " << a[i] << std::endl;
		} else  {
			std::cout << " " << a[i];
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

int 
main()
{

	int t1[] = {8, 8, 8, 8, 8};
	std::cout << "T1 test:" << std::endl;
	merge_sort(t1, sizeof(t1)/sizeof(int));
	print_array(t1, sizeof(t1)/sizeof(int));


	int t2[3] = {8, 7, 6};
	std::cout << "T2 test:" << std::endl;
	merge_sort(t2, sizeof(t2)/sizeof(int));
	print_array(t2, sizeof(t2)/sizeof(int));

	int t3[10000];
	default_random_engine dre;
	uniform_int_distribution<int> di(1,1000); 

	for (int i = 0; i < 10000; i++) {
		t3[i] = di(dre);
	}
	std::cout << "T3 test, before:" << std::endl;
	print_array(t3, sizeof(t3)/sizeof(int));
	merge_sort(t3, sizeof(t3)/sizeof(int));
	std::cout << "T3 test, After:" << std::endl;
	print_array(t3, sizeof(t3)/sizeof(int));

	return 0;
}



