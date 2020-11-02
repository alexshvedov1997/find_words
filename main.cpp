#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <ctype.h>

using namespace std;
 typedef pair<short, short> location;
 typedef vector<location> loc;
 typedef vector<string> text;
 typedef pair<text*, loc*>  text_loc;

vector<string>* retrieve();
text_loc* separate_words(const vector<string> *text_file);
void filter_text(vector<string> *words, string filter);
void string_caps(vector<string> words);

int main(){
   
    vector<string> *vec = retrieve();
   puts("OK!");
//   text_loc * words_positions = separate_words(vec);
text_loc * text = new text_loc;
text = separate_words(vec);
   puts("OK_2!");
  //  for( int i = 0; i < words_positions->first->size(); i++){
 //       cout<<(*words_positions->first)[i]<<" positions: "<< endl;
 //   }
//cout<<(*words_positions->first)[2]<<" positions: "<< endl;
    return 0;
}


vector<string>* retrieve(){
    string file_name;
    cout<<"please enter file name"<<endl;
    cin>>file_name;
    ifstream infile(file_name.c_str(), ios::in);
    if(!infile){
        cerr<<"opps! unable to open file "<<file_name<<"------- banding out! \n"<<endl;
        exit(-1);
    }
    else
    {
        cout<<"\n";
    }
    vector<string> *lines_of_text = new vector<string>;
    string textline;
    int linenum = 0;
    typedef pair<string::size_type, int> stats;
    stats maxline;
    while(getline(infile, textline, '\n')){
        cout<<"line read: " << textline<< endl;
        if(maxline.first < textline.size()){
            maxline.second = textline.size();
            maxline.first = linenum;
        }
        lines_of_text->push_back(textline);
        linenum++;
    }

    return lines_of_text;
    }

text_loc* separate_words(const vector<string> *text_file){
    vector<string> *words = new vector<string> ;
    vector<location> *locations = new vector<location>;
    short line_pos = 0;
    for(; line_pos < text_file->size(); ++line_pos){
        short word_pos = 0;
        string text_line = (*text_file)[line_pos];
        string::size_type pos = 0, prev_pos = 0;
        while((pos = text_line.find_first_of(' ', pos) != string::npos)){
            words->push_back(text_line.substr(prev_pos, pos-prev_pos));
            locations->push_back(make_pair(line_pos, word_pos));
            ++word_pos, prev_pos = ++pos;
        }
        words->push_back(text_line.substr(prev_pos, pos-prev_pos));
         locations->push_back(make_pair(line_pos, word_pos));
    }
    return new text_loc(words, locations);
}

void filter_text(vector<string> *words, string filter){
vector<string>::iterator iter = words->begin();
vector<string>::iterator iter_end = words->end();

if(!filter.size())
    filter.insert(0,"\",.");
while(iter != iter_end){
    string::size_type pos =0;
    while((pos = (*iter).find_first_of(filter, pos)) != string::npos)
                (*iter).erase(pos);
    iter++;
}
}

void string_caps(vector<string>* words){
    vector<string>::iterator iter = words->begin();
    vector<string>::iterator iter_end = words->end();
    string caps( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
    while(iter != iter_end){
        string::size_type pos = 0;
        while((pos = (*iter).find_first_of(caps, pos)) != string::npos)
            (*iter)[pos] = tolower(pos);
        iter++;
    }

}

