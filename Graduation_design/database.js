//test javascript



// real code block
var index = 10;
var current_DB_index;

//default operate database is word_list_order
var operate_db_name = "word_list_order";

function getindex()
{
    return index;
}

function setindex( idx )
{
    index = idx;
}

// set & get get_operate_db_table_name()

function get_operate_db_table_name(  )
{
    var db = getdatabase();
    var result_set;

    var str = "SELECT info_value FROM extra_info WHERE info_key = 'operate_db_table_name';"
    console.log( str );
    db.transaction( function(tx) {
        var result = tx.executeSql( str );
        result_set = result;
        console.log( result.rows.length )
        if (result.rows.length != 0 ) {
            console.log( " exec success ");
        }
        else {
            result_set = "Unknown";
            console.log( " exec faliure");
        }
    })
    return result_set.rows[0].info_value;
}



// set & get set_operate_db_table_name()

function set_operate_db_table_name( db_name )
{
    var db = getdatabase();
    var result_set;

    var str = "UPDATE extra_info SET info_value='"+db_name+
            "' WHERE info_key='operate_db_table_name';";
    console.log( str );
    db.transaction( function(tx) {
        var result = tx.executeSql( str );
        result_set = result;
        console.log( result.rows.length )
        if (result.rows.length === 0 ) {
            console.log( " exec success ");
        }
        else {
            result_set = "Unknown";
            console.log( " exec faliure");
        }
    })

}





// set & get current_db_index
function get_current_DB_index( )
{
    var db = getdatabase();
    var result_set;

    var str = "SELECT db_table_current_index FROM para_info WHERE db_table_name = '" +get_operate_db_table_name()+"';"
    console.log( str );
    db.transaction( function(tx) {
        var result = tx.executeSql( str );
        result_set = result;
        console.log( result.rows.length )
        if (result.rows.length != 0 ) {
            console.log( " exec success ");
        }
        else {
            result_set = "Unknown";
            console.log( " exec faliure");
        }
    })
    console.log( result_set.rows[0].db_table_current_index );
    return result_set.rows[0].db_table_current_index;
}

// set & get current_db_index
function set_current_DB_index( idx )
{
    var db = getdatabase();
    var result_set;

    var str = "UPDATE para_info SET db_table_current_index="+idx+
            " WHERE db_table_name='"+get_operate_db_table_name()+"'"+
            ";"
    console.log( str );
    db.transaction( function(tx) {
        var result = tx.executeSql( str );
        result_set = result;
        console.log( result.rows.length )
        if (result.rows.length != 0 ) {
            console.log( " exec success ");
        }
        else {
            result_set = "Unknown";
            console.log( " exec faliure");
        }
    })

}




function getdatabase() {
    return LocalStorage.openDatabaseSync("word_list", "1.0", "word_list_database", 100000);
}

function readData(name) {
    var db = getdatabase();
    var res=""
    var res_index="";
    var res_word="";
    var res_soundmark="";
    var res_meaning="";

    var result_set;

    db.transaction( function(tx) {
        var result = tx.executeSql("select * from word_list_order where word=?;", [name]);
        if (result.rows.length > 0) {
            res=result
            res_index = result.rows.item(0).word_index
            res_word = result.rows.item(0).word
            res_soundmark = result.rows.item(0).soundmark
            res_meaning = result.rows.item(0).meaning

            result_set = [res_index, res_word, res_soundmark, res_meaning];

            console.log(result_set[2])


        } else {
            result_set = "Unknown";
        }
    })
    return result_set;
}

function insertData(name, value) {
    var res = "";
    if(!db) { return; }
    db.transaction( function(tx) {
        var result = tx.executeSql("INSERT OR REPLACE INTO word_list_order VALUES (?,?);", [name, value]);
        if (result.rowsAffected > 0) {
          res = "OK";
        } else {
          res = "Error";
        }
    })
    return res
}


function readData_by_index( idx ) {
    //debug
//    console.log("readDate_by_index, The index is : " + idx);


    var db = getdatabase();

    var res=""
    var res_index="";
    var res_word="";
    var res_soundmark="";
    var res_meaning="";

    var result_set;

    var sql_str = "select * from "+get_operate_db_table_name()+" where word_index="+idx+";"

    console.log( sql_str );
    db.transaction( function(tx) {
        var result = tx.executeSql(sql_str);
        if (result.rows.length > 0) {


            res=result
            res_index = result.rows.item(0).word_index
            res_word = result.rows.item(0).word
            res_soundmark = result.rows.item(0).soundmark
            res_meaning = result.rows.item(0).meaning

            result_set = [res_index, res_word, res_soundmark, res_meaning];

            console.log(result_set[2])

        } else {
            result_set = "Unknown";
        }
    })
    return result_set;
}


// page_2 load database table as word_list
function load_db_table_as_word_list( )
{
    var db = getdatabase();
    var result_set = [];

//    var str = ".tables;"
    var str = "SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;";

    db.transaction( function(tx) {
        var result = tx.executeSql( str );
        console.log( result.rows.length )
        if (result.rows.length > 0 ) {
            console.log( "js: exec success ");
            for( var i = 0; i < result.rows.length; i++ )
            {
                var result_temp = result.rows[i].name
                console.log( result_temp );
//                result_set = []
                result_set[i] = result_temp
            }
            for( var ii = 0; ii < result_set.length; ii++ )
            {
                console.log( "js: " + result_set[ii] )
            }

//            return ";
        }
        else {
            result_set = "Unknown";
            console.log( "js: exec faliure");
            return result_set;
        }
    })

    return result_set;

}



// page_2   create & delete database table
//////////////////////////////////////////////////////////////////////////
// create a db table at the same time the model add one new item
function create_db_table( add_table_name )
{
    var db = getdatabase();
    var result_set;

    var str = "CREATE TABLE " + add_table_name +
            "( " +
            "word_index INT," +
            "word VARCHAR," +
            "soundmark VARCHAR," +
            "meaning VARCHAR," +
            "study_count INT," +
            "is_marked bool);";
    console.log( str );
    db.transaction( function(tx) {
        var result = tx.executeSql( str );
//        console.log( result.rows.length )
        if (result.rows.length === 0 ) {
            console.log( " exec success ");
        }
        else {
            result_set = "Unknown";
            console.log( " exec faliure ");
        }
    })

    // write para_info to para_info_table
    var para_info_str = "INSERT INTO para_info values('" +
           add_table_name +
            "', 0, 0, 0);"
    console.log( "js: " +  para_info_str );
    db.transaction( function(tx) {
        var result = tx.executeSql( para_info_str );
        console.log( result.rows.length )
        if (result.rows.length === 0 ) {
            console.log( " exec success ");
        }
        else {
            result_set = "Unknown";
            console.log( " exec faliure ");
        }
    })

    return true;
}


// delete a db table at the same time the model delete one table
function delete_db_table( del_table_name )
{
    var db = getdatabase();
    var result_set;

    var str = "DROP TABLE " + del_table_name + ";";
    console.log( str );
    db.transaction( function(tx) {
        var result = tx.executeSql( str );
        console.log( result.rows.length )
        if (result.rows.length === 0 ) {
            console.log( " exec success ");
        }
        else {
            result_set = "Unknown";
            console.log( "exec faliure");
        }
    })


    // modify para_info to para_info_table
    var para_info_str = "DELETE FROM para_info where db_table_name = '" +
           del_table_name +
            "';"
    console.log( "js: " +  para_info_str );
    db.transaction( function(tx) {
        var result = tx.executeSql( para_info_str );
        console.log( result.rows.length )
        if (result.rows.length === 0 ) {
            console.log( " exec success ");
        }
        else {
            result_set = "Unknown";
            console.log( " exec faliure ");
        }
    })

    return false;
}
