void SLS::deleteAuthor(int Id)
{
    //store index into Map
    store_Index_In_Map();
    auto check = binarySearch(authorIds,Id);
    if (check != -1)
    {
        char List[10];
        ////get Avail List
        authorFile.open("file.txt" , ios::in);
        int ByteOffset=indexing[Id];
        ///get size of record
        string record;
        authorFile.seekg(ByteOffset,ios::beg);
        getline(authorFile,record,'\r');
        string size=to_string(record.length());
        authorFile.seekg(ios::beg);
        authorFile.getline(List,sizeof (List));
        authorFile.close();

        ////get byte offset of deleted record
        string Byte=to_string(ByteOffset);
        authorFile.open("file.txt", std::ios::in | std::ios::out);
        authorFile.seekp(ios::beg);
        authorFile.write(Byte.c_str(),2);
        authorFile.seekp(ByteOffset,ios::beg);
        ///insert size and pre deleted
        authorFile.write("*",1);
        authorFile.write(List,2);
        authorFile.write("|",1);
        authorFile<<size;
        authorFile.write("|",1);
        authorFile.close();
        auto it = indexing.find(Id);
        indexing.erase(it);
        retrieve_into_index();
        cout<<"Done\n";

    }
    else
        cout<<"This author doesn't exist\n";
}
void SLS::Search_By_Primary(int Id)
{
    int check= binarySearch(authorIds,Id);
    store_Index_In_Map();
//    auto check = indexing.find(Id);
    if (check != -1) {
        authorFile.open("file.txt", ios::in);
        long ByteOffset=indexing[Id];
        authorFile.seekg(ByteOffset,ios::beg);
        //don't want print without it
        authorFile.get();
        string line;
        getline(authorFile, line);
        cout<<"the Author Founded.. \n";
        istringstream ss(line);
        string token;
        vector<std::string> tokens;
        while (std::getline(ss, token, '|')) {
            tokens.push_back(token);
        }
        cout<<"Author's ID : "<<tokens[0]<<endl;
        cout<<"Author's name : "<<tokens[1]<<endl;
        cout<<"Author's Address : "<<tokens[2]<<endl;
    }
    else
    {
        cout<<"Sorry this author not exist\n";
    }
}
