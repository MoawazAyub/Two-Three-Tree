# include <iostream>

using namespace std;

template <class T>
class Twothreetree
{
	struct Node
	{
		T data0;
		T data1;
		T data2;
		Node * left, * right, * mid;
		bool empty;
		bool full;
		bool overflow;
		bool half;
		bool coverflow;
	    Node * cleft;
	
	};
	Node * root;
	int size;

	Node* createnode(const T & obj)
	{
		Node* temp     = new Node;
		temp->left     = NULL;
		temp->cleft     = NULL;
		temp->right    = NULL;
		temp->mid      = NULL;
		temp->data1    = obj;
		temp->empty    = false;
		temp->full     = false;
		temp->overflow = false;
		temp->coverflow = false;
		temp->half     = true;

		return temp;
	
	}



public:

	bool isempty()
	{
		if(size == 0)
		{
			return true;
		
		}

		else
		{
			return false;
		
		}
	
	}

	Twothreetree()
	{
		root = NULL;
		size = 0;
	}

	void insert(const T & obj)
	{
		if(isempty())
		{
			root = createnode(obj);
			size++;
		
		}


		else
		{
		Node* curr = root;
		Node* prev = NULL;

		while(curr != NULL)
		{
			prev = curr;


			if(curr->full == true)
			{
			if(curr->data1 <= obj  && curr->data2 > obj)
			{
				curr = curr->mid;
			
			}

			else if(curr->data2 <= obj)
			{
				curr = curr->right;
			
			}
			else if(curr->data1 > obj)
			{
				curr = curr->left;
			
			}
		
			}
			//-----------------------------------------------------
			else if(curr->half == true)
			{
			

		    if(curr->data1 <= obj)
			{
				curr = curr->mid;
			
			}
			else if(curr->data1 > obj)
			{
				curr = curr->left;
			
			}
		
			}
		
		}

		//-----------------------------------------------------------end of while

		if(prev->half == true)
		{
			prev->data2 = obj;

			if(prev->data2 < prev->data1)
			{
				swap(prev->data1,prev->data2);
			
			}

			prev->half     = false;
			prev->empty    = false;
			prev->full     = true;
			prev->overflow = false;
		
		}

		else if(prev->full == true)
		{
			prev->data0 = obj;

		
			prev->half     = false;
			prev->empty    = false;
			prev->full     = false;
			prev->overflow = true;


			if(prev->data0 > prev->data1 && prev->data0 < prev->data2)
			{
				swap(prev->data0,prev->data1);
			
			}

			else if(prev->data0 > prev->data1 && prev->data0 > prev->data2)
			{
				swap(prev->data0,prev->data1);
				swap(prev->data1,prev->data2);
			
			}

			//---------------------------------------------- rotation
			//-----------------------------------------------------------find parent
			Node * pre2 = NULL;
start:			curr = root;

    		while(curr != prev)
			{
				pre2 = curr;

			if(curr->full == true)
			{
			if(curr->data1 <= obj  && curr->data2 > obj)
			{
				curr = curr->mid;
			
			}

			else if(curr->data2 <= obj)
			{
				curr = curr->right;
			
			}
			else if(curr->data1 > obj)
			{
				curr = curr->left;
			
			}
		
			}
			//-----------------------------------------------------
			else if(curr->half == true)
			{
			

		    if(curr->data1 <= obj)
			{
				curr = curr->mid;
			
			}
			else if(curr->data1 > obj)
			{
				curr = curr->left;
			
			}
		
			}
			
			}

			//--------------------------------------------------------end of find paret while
			if(pre2 == NULL && prev->coverflow == false)
			{
				prev->left = createnode(prev->data0);
				prev->mid = createnode(prev->data2);
				prev->data0 = T();
				prev->data2 = T();

				size = size + 2;

			prev->half     = true;
			prev->empty    = false;
			prev->full     = false;
			prev->overflow = false;
				
			}

			else if(pre2 == NULL && prev->coverflow == true)
			{
				Node * temp;
				temp = createnode(prev->data1);
				temp->mid = createnode(prev->data2);
				prev->data1 = prev->data0;

				temp->mid->mid = prev->right;
				temp->mid->left = prev->mid;
				prev->mid = prev->left;
				prev->left = prev->cleft;
				prev->cleft = NULL;
				
				temp->left = prev;
				prev->right = NULL;
				root = temp;
			prev->half     = true;
			prev->empty    = false;
			prev->full     = false;
			prev->overflow = false;
			prev->coverflow = false;
			
			}

			else
			{
				bool rotationsuccessful = false;
				bool one = false;
				bool two = false;

				if(pre2->half == true)
				{
					if(prev == pre2->left)
					{
					if(pre2->mid->half == true)
					{
						rotationsuccessful = true;
					}
					if( rotationsuccessful == true )
					{
						pre2->mid->data2 = pre2->mid->data1;
						pre2->mid->data1 = pre2->data1;
						pre2->data1      = prev->data2;
						prev->data2      = prev->data1;
						prev->data1      = prev->data0;
						prev->data0      = T();

						pre2->mid->right = pre2->mid->mid;
						pre2->mid->mid   = pre2->mid->left;
						pre2->mid->left  = prev->right;
						prev->right      = prev->mid;
						prev->mid        = prev->left;
						prev->left       = prev->cleft;
						prev->cleft      = NULL;

						prev->half     = false;
			            prev->empty    = false;
			            prev->full     = true;
			            prev->overflow = false;
						 prev->coverflow = false;


						pre2->mid->half     = false;
			            pre2->mid->empty    = false;
			            pre2->mid->full     = true;
			            pre2->mid->overflow = false;
					
					}
					}

					else if(prev == pre2->mid)
					{
					if(pre2->left->half == true)
					{
						rotationsuccessful = true;
					}
					if( rotationsuccessful == true )
					{
						
						pre2->left->data2 = pre2->data1;
						pre2->data1      = prev->data0;
						
						//prev->data0      = T();

						pre2->left->right = prev->cleft;
						prev->cleft       = NULL;

						prev->half     = false;
			            prev->empty    = false;
			            prev->full     = true;
			            prev->overflow = false;
						prev->coverflow = false;


						pre2->left->half     = false;
			            pre2->left->empty    = false;
			            pre2->left->full     = true;
			            pre2->left->overflow = false;
					
					}
					}

				
				}

				else if(pre2->full == true)
				{    
					
					if(prev == pre2->left)
					{
					if(pre2->mid->half == true)
					{
						rotationsuccessful = true;
					}
					if( rotationsuccessful == true )
					{
						pre2->mid->data2 = pre2->mid->data1;
						pre2->mid->data1 = pre2->data1;
						pre2->data1      = prev->data2;
						prev->data2      = prev->data1;
						prev->data1      = prev->data0;
						prev->data0      = T();

						pre2->mid->right = pre2->mid->mid;
						pre2->mid->mid   = pre2->mid->left;
						pre2->mid->left  = prev->right;
						prev->right      = prev->mid;
						prev->mid        = prev->left;
						prev->left       = prev->cleft;
						prev->cleft      = NULL;

						prev->half     = false;
			            prev->empty    = false;
			            prev->full     = true;
			            prev->overflow = false;
						prev->coverflow = false;


						pre2->mid->half     = false;
			            pre2->mid->empty    = false;
			            pre2->mid->full     = true;
			            pre2->mid->overflow = false;
					
					}


					
	 			    
				    
				}     


					else if(prev == pre2->right)
					{
					if(pre2->mid->half == true)
					{
						rotationsuccessful = true;
					}
					if( rotationsuccessful == true )
					{
						pre2->mid->data2 = pre2->data2;
						pre2->data2      = prev->data0;		
						prev->data0      = T();

						pre2->mid->right = prev->cleft;
						prev->cleft      = NULL;

						prev->half     = false;
			            prev->empty    = false;
			            prev->full     = true;
			            prev->overflow = false;


						pre2->mid->half     = false;
			            pre2->mid->empty    = false;
			            pre2->mid->full     = true;
			            pre2->mid->overflow = false;
					
					}


					
	 			    
				    
				} 
					
					else if(prev == pre2->mid)
					{
					if(pre2->left->half == true)
					{
						one = true;
					}

					if(pre2->right->half == true)
					{
						two = true;
					}

					if( one == true )
					{
						pre2->left->data2 = pre2->data1;
						pre2->data1      = prev->data0;
						
						//prev->data0      = T();

						pre2->left->right = prev->cleft;
						prev->cleft       = NULL;

						prev->half     = false;
			            prev->empty    = false;
			            prev->full     = true;
			            prev->overflow = false;
						prev->coverflow = false;


						pre2->left->half     = false;
			            pre2->left->empty    = false;
			            pre2->left->full     = true;
			            pre2->left->overflow = false;
						rotationsuccessful   = one | two; 
					}

					else if( two == true )
					{
						pre2->right->data2 = pre2->right->data1;
						pre2->right->data1 = pre2->data2;
						pre2->data2        = prev->data2;
						prev->data2        = prev->data1;
						prev->data1        = prev->data0;
						
						
						//prev->data0      = T();

						pre2->right->right = pre2->right->mid;
						pre2->right->mid   = pre2->right->left;
						pre2->right->left  = prev->right;
						prev->right        = prev->mid;
						prev->mid          = prev->left;
						prev->left         = prev->cleft;
						prev->cleft        = NULL;

						prev->half     = false;
			            prev->empty    = false;
			            prev->full     = true;
			            prev->overflow = false;
						prev->coverflow = false;


						pre2->right->half     = false;
			            pre2->right->empty    = false;
			            pre2->right->full     = true;
			            pre2->right->overflow = false;
						rotationsuccessful    = one | two;
					
					}


					
	 			    
				    
				} 
					}

					//-------------------------------------------------------------------

					if (rotationsuccessful == false)
					{
						
							if(pre2->half == true)
							{
								if(prev == pre2->left)
								{
									pre2->data2 = pre2->data1;
									pre2->data1 = prev->data1;
									prev->data1 = prev->data2;
										

									pre2->right = pre2->mid;
									pre2->mid   = pre2->left;
									pre2->left  = createnode(prev->data0);

									pre2->left->left = pre2->mid->cleft;
									pre2->left->mid  = pre2->mid->left;

									pre2->mid->left  = pre2->mid->mid;
									pre2->mid->mid   = pre2->mid->right;
									pre2->mid->right = NULL;

									pre2->left->half = true;
									pre2->left->full = false;
									pre2->left->overflow = false;
									pre2->left->empty = false;
									pre2->left->coverflow = false;

									pre2->mid->half = true;
									pre2->mid->full = false;
									pre2->mid->overflow = false;
									pre2->mid->empty = false;
									pre2->mid->coverflow = false;
 

									pre2->half = false;
									pre2->full = true;
									pre2->overflow = false;
									pre2->empty = false;
									pre2->coverflow = false;
 
									
						
								}

								else if(prev == pre2->mid)
								{
									
									pre2->data2 = prev->data1;
									prev->data1 = prev->data0;
										

									
									
									pre2->right  = createnode(prev->data2);

									pre2->right->mid = pre2->mid->right;
									pre2->right->left  = pre2->mid->mid;

									pre2->mid->mid  = pre2->mid->left;
									pre2->mid->left   = pre2->mid->cleft;
									pre2->mid->right = NULL;

									pre2->right->half = true;
									pre2->right->full = false;
									pre2->right->overflow = false;
									pre2->right->empty = false;
									pre2->right->coverflow = false;

									pre2->mid->half = true;
									pre2->mid->full = false;
									pre2->mid->overflow = false;
									pre2->mid->empty = false;
									pre2->mid->coverflow = false;
 
									pre2->half = false;
									pre2->full = true;
									pre2->overflow = false;
									pre2->empty = false;
									pre2->coverflow = false;
								
								}
							
							}
						
						else if(pre2->full == true)
						{
							if(prev == pre2->left)
							{
								pre2->data0 = prev->data1;
								prev->data1 = prev->data2;

								pre2->cleft = createnode(prev->data0);

								pre2->cleft->left  = prev->cleft;
								pre2->cleft->mid = prev->left;
								prev->left        = prev->mid;
								prev->cleft       = NULL;
								prev->mid         = prev->right;
								prev->right       = NULL;


								pre2->coverflow = true;
								pre2->half      = false;
								pre2->full      = true;
								pre2->empty     = false;
								pre2->overflow  = true;

								prev->coverflow = false;
								prev->half      = true;
								prev->full      = false;
								prev->empty     = false;
								prev->overflow  = false;

								prev = pre2;
								pre2 = NULL;

								goto start;
							
							}

							else if(prev == pre2->mid)
							{
								pre2->data0 = pre2->data1;
								pre2->data1 = prev->data1;
								pre2->cleft = pre2->left;
								pre2->left  = createnode(prev->data0);
								prev->data1 = prev->data2;
								pre2->left->left = pre2->mid->cleft;
								pre2->left->mid  = pre2->mid->left;
								pre2->mid->left  = pre2->mid->mid;
								pre2->mid->mid   = pre2->mid->right;
								pre2->mid->right = NULL;


								pre2->coverflow = true;
								pre2->half      = false;
								pre2->full      = true;
								pre2->empty     = false;
								pre2->overflow  = true;

								prev->coverflow = false;
								prev->half      = true;
								prev->full      = false;
								prev->empty     = false;
								prev->overflow  = false;

								prev = pre2;
								pre2 = NULL;

								goto start;
							
							}

							else if(prev == pre2->right)
							{
								pre2->data0 = pre2->data1;
								pre2->data1 = pre2->data2;
								pre2->data2 = prev->data1;
								pre2->cleft = pre2->left;
								pre2->left  = pre2->mid;
								pre2->mid  = createnode(prev->data0);
								prev->data1 = prev->data2;
								pre2->mid->left = pre2->right->cleft;
								pre2->mid->mid  = pre2->right->left;
								pre2->right->left  = pre2->right->mid;
								pre2->right->mid   = pre2->right->right;
								pre2->right->right = NULL;


								pre2->coverflow = true;
								pre2->half      = false;
								pre2->full      = true;
								pre2->empty     = false;
								pre2->overflow  = true;

								prev->coverflow = false;
								prev->half      = true;
								prev->full      = false;
								prev->empty     = false;
								prev->overflow  = false;

								prev = pre2;
								pre2 = NULL;

								goto start;
							
							}
							
							
							
						}
						
					
					}

					//-------------------------------------------------------------------
			
			}//first merge
		
		}//-------------------------------back

		//--------------------------------end of else
		}
	
	}

};



void main()
{
	cout<<endl;
	Twothreetree<int> t1,t2;
	t1.insert(6);
	t1.insert(7);
	t1.insert(4);
	t1.insert(8);

	
	t1.insert(9);
	
	t1.insert(3);
	
    t1.insert(2);
	t1.insert(1);
	t1.insert(0);
	t2 = t1;
}