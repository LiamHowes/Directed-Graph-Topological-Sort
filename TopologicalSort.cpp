//Liam Howes 5880331

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

string vertices[20];
stringstream output;
bool edges[20][20] = {false};
bool visited[20] = {false};

int indegrees[20];

void TopSort(int num_vertices){
    // 2)find an univisited vertex with 0 indegree
    int vertex=-1;
    for(int i=0; i<num_vertices; i++){ 
        if(indegrees[i]==0 && visited[i]==false){ // found one
            vertex = i;
            visited[i] = true;
            break;
        }
    }
    if(vertex==-1){ // didn't find one
        bool all_visited = true;
        // have they all been visited?
        for(int i=0; i<num_vertices; i++){
            if(visited[i]==false){
                all_visited = false;
            }
        }
        // if they haven't, and no vertex with 0 indegree, then terminate.
        if(all_visited==false){
            cout<<"\nSort Terminated. No topological sort possible (cyclic dependencies).\n";
            output.str(string());
        }
    }
    else{
        // 2-a) process (print vertex)
        output << vertices[vertex];
        output << " ";

        // 2-b) for each outbound edge of vertex, reduce its indegree by 1
        for(int j=0; j<num_vertices; j++){
            if(edges[vertex][j]==true){
                indegrees[j]--;
            }
        }
        TopSort(num_vertices);
    }
}


int main(){
    string filename;
    int num_vertices;
    int num_edges;
    
    bool file_found = false;

    while(file_found == false){ 
        cout<<"Enter Graph Filename: ";
        cin>>filename;

        cout<<"Using "<<filename<<endl;
        const char *cstr = filename.c_str();
        ifstream file(cstr, ios::in);
        
        if(file.is_open()){
            cout<<"File Opened\n";
            file_found = true;
        // - - - - - LOAD GRAPH DATA - - - - - //
            // vertices
            file>>num_vertices;
            for(int i=0; i<num_vertices-1; i++){
                string line;
                getline(file, line, '\t');
                stringstream ss(line);
                ss>>vertices[i];
            }
            string line;
            getline(file, line, '\n');
            stringstream ss(line);
            ss>>vertices[num_vertices-1];
            // edges
            file>>num_edges;
            string pair;
            int vertex1, vertex2;
            for(int i=0; i<num_edges; i++){
                file>>vertex1;
                file>>vertex2;
                edges[vertex1][vertex2] = true;
            }
        // - - - - - GRAPH DATA LOADED - - - - - //
            cout<<"\nNumber of Vertices: "<<num_vertices<<endl;
            cout<<"Vertices: \n";
            for(int i=0; i<num_vertices; i++){
                cout<<"["<<i<<":"<<vertices[i]<<"]  ";
            }
            cout<<endl;
        // - - - - - Print Edge Relationships - - - - - //
            cout<<"\nNumber of Edges: "<<num_edges<<endl;
            cout<<"Edges: \n";
            for(int i=0; i<num_vertices; i++){
                cout<<vertices[i]<<" -> ";
                for(int j=0; j<num_vertices; j++){
                    if(edges[i][j]==true){
                        cout<<vertices[j]<<"  ";
                    }
                }
                cout<<endl;
            }
        // - - - - - Topological Sort - - - - - //
            // Top Sort starting with that 0 indegree vertex
            // 1) Determine the indegrees of all vertices in the graph
            for(int j=0; j<num_vertices; j++){
                int count = 0;
                for(int i=0; i<num_vertices; i++){
                    if(edges[i][j]==true){
                        count++;
                    }
                }
                indegrees[j] = count;
            }
            cout<<"\nTopological Sort:\n";
            TopSort(num_vertices);
            cout<<output.str();
            cout<<endl;

            file.close();
        }
        else cout<<"ERROR: Filename Not Found\n";
    }
    return 0;
}