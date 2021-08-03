#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#define size_of_alphabet (26)

//only considering lower case letters

vector<string> v;
map<string,int> mp;

//TrieNode structure
struct TrieNode
{
    TrieNode *child[size_of_alphabet];
    bool isEnd_of_word;

    TrieNode()
    {
        bool isEnd_of_word=false;

        for(int i=0;i<26;i++)
        {
            child[i]=NULL;
        }
    }

};

//insert function inserts words in to Trie data structure

void insert(TrieNode *root,  const string key )
{
    mp[key]++;
    struct TrieNode *current = root;

    for (int level = 0; level < key.length(); level++)
    {
        int index = key[level]-'a';
        if (current->child[index]==NULL)
            current->child[index] = new TrieNode();

        current = current->child[index];
    }

    // mark last node as leaf
    current->isEnd_of_word = true;
}

//searches for a word and if found returns true else returns false

bool search(TrieNode *root, const string key)
{
    int length = key.length();
    TrieNode *current = root;
    for (int level = 0; level < length; level++)
    {
        int index = key[level]-'a' ;

        if (current->child[index]==NULL)
        {
            return false;
        }


        current = current->child[index];
    }

    return (current != NULL && current->isEnd_of_word);
}


bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i <size_of_alphabet ; i++)
        if (root->child[i])
            return 0;
    return 1;
}

void suggestions_of_given_word(struct TrieNode* root, string word )
{
    //words that were starting with given string word are kept in avector
    if (root->isEnd_of_word)
    {
        v.push_back(word);
    }


    if (isLastNode(root))
        return;

    for (int i = 0; i < size_of_alphabet; i++)
    {
        if (root->child[i])
        {
            // append current character to word string
            word.push_back(97 + i);
            // recurring for the remaining
            suggestions_of_given_word(root->child[i], word);
            // remove last character so that some other suggestions also can be printed
            word.pop_back();
        }
    }

}

int Suggestions_printing(TrieNode* root, const string user_input_word)
{

    struct TrieNode* current = root;

    // Check if prefix is present and find the node with last character of given string.

    int n = user_input_word.length();

    for (int level = 0; level < n; level++)
    {
        int index =user_input_word[level]-'a';

        // If there is no string with the given word it returns 0
        if (current->child[index]==NULL)
            return 0;

        current = current->child[index];
    }

    //checking if there is a prefix for given word
    bool isWordpresent = (current->isEnd_of_word == true);

    // If prefix is last node of tree (has no
    // children)
    bool isLast_of_word = isLastNode(current);

    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isWordpresent && isLast_of_word)
    {

        cout<<user_input_word<<endl;
        return -1;
    }

    // If there are are words present after last character of given word
    // then we consider all the suggestions having given word as a prefix

    if (!isLast_of_word)
    {
        //this user_input_word will be prefix for some other words starting with this
        string prefix = user_input_word;
        suggestions_of_given_word(current , prefix);
        return 1;
    }
    return 0;
}

/*
void display( TrieNode* root, string str, int level)
{
	// If node is leaf node, it indicates end
	// of string, so a null character is added
	// and string is displayed
	if (isLastNode(root))
	{

		cout << str << endl;
	}

	int i;
	for (i = 0; i < size_of_alphabet; i++)
	{
		// if NON NULL child is found
		// add parent key to str and
		// call the display function recursively
		// for child node
		if (root->child[i])
		{
			str.push_back(i + 'a');
			display(root->child[i], str, level + 1);
			str.pop_back();
		}
	}
}
*/
bool sortbysecond(const pair<string,int> &a, const pair<string,int> &b)
{

    if(a.second==b.second)
    {

        return (a.first<b.first);
    }
    return a.second>b.second;
}

vector<string> findtopmost3words()
{
    vector<pair<string,int>> vect;
    vector<string> top3_vector;
    if(v.size()<=3) return v;
    for(int i=0;i<v.size();i++)
    {
        vect.push_back(make_pair(v[i],mp[v[i]]));
    }
    sort(vect.begin(),vect.end(),sortbysecond);

    //this for loop shows the frequency of matching words with user_input_word
    /* for(int i=0;i<ve.size();i++)
    {
      cout<<vect[i].first<<"->"<<vect[i].second<<endl;
    } */
    int index=0;
    for(int i=0;i<vect.size();i++)
    {
        top3_vector.push_back(vect[i].first);

    }
    return top3_vector;

}



int main()
{
    TrieNode *root=new TrieNode();

    fstream f;
    ofstream fout;
    ifstream fin;
    fin.open("C:\\Users\\deepu\\Desktop\\testing_project.txt");
    fout.open ("C:\\Users\\deepu\\Desktop\\testing_project.txt",ios::app);
    string enter_input;
    cout<<"please enter a word of atleast length 2"<<endl;
    cin>>enter_input;
    if(fin.is_open())
    {
      cout<<endl;
      cout<<"Searching for words that your input word matches with..........."<<endl;
      cout<<endl;
      fin.close();
      fout.close();

      string word;
      f.open("C:\\Users\\deepu\\Desktop\\testing_project.txt");
      while (f >> word)
      {
            insert(root,word);

      }
      string res="";
      cout<<endl;


      cout<<"printing suggestions that matches with user input"<<endl;
      cout<<endl;

      string enter_word;

      if(Suggestions_printing(root,enter_input)==0)
      {
          cout<< "no word matches sry"<<endl;
          cout<<endl;
          cout<<"enter your word for next time to be suggested"<<endl;

          //asks for user to enter his full words rather than first 2 or 3 letters
          //so that word can be shown next time

          cin>>enter_word;

          fin.open("C:\\Users\\deepu\\Desktop\\testing_project.txt");

          fout.open ("C:\\Users\\deepu\\Desktop\\testing_project.txt",ios::app);

          if(fin.is_open())
          {

              //space to give for later and previous word

              fout<<" ";

              //reading the entered word in to file

              fout<<enter_word;

              //closing file

              fin.close();
              fout.close();
          }

          //inserting entered word in to trie data structure

          insert(root,enter_word);
          return 0;
      }


      vector<string> words_stored;

      words_stored=findtopmost3words();

      //printing all the highest frequency words that mateches with user input

      for(int i=0;i<words_stored.size();i++)
      {
          cout<<words_stored[i]<<" ";

      }
    cout<<endl;
   }

    return 0;
}
