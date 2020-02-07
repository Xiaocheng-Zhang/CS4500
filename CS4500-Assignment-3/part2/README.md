# Dataframe API description:
	Our dataframe supports int, float, bool, String Columns and potentially other types of data in column list format.
    *All these types should be an Object type*
	The functions and its use cases are listed at following:

- Dataframe df = new Dataframe(a,b,c,...)
	Dataframe constructor. The constructor can take one or more data columns.
	Columns can have different lengths. The shorter column will be filled Null pointer at the end of column.

- df.get(m,n)
	Return the value at row m and column n.
	The coordinates begins with row position, then followed by a comma, and ends with the column position. 
	Indexes will be asserted within dataframe's range.

- df.get("m","n")
	Return the value at which row's name is "m" and column's name is "n"
	The coordinates begins with row name, then followed by a comma, and 
	ends with the column name.
	Names will be asserted.

- df.nrow()
	Return the number of data rows in the dataframe

- df.ncol()
	Return the number of data columns in the dataframe

- df.isnull() 
	Return a dataframe filled with true and false, indicating what is null 
	what is not null. The returned dataframe has same length and height.

- df.notnull() 
	Opposite of isnull()

- df.dropna()
	Drop rows that have one or more nulls. Only the row that do not have 
	nulls will be left.

- df.insert(i, name, values)
	Insert a column into dataframe. i is the index where column is inserted 
	name is the name of the column. values are simply the column.

- df.drop(i)
	Drop the ith column

- df.drop("m")
	Drop the column whose name is "m"

- df.dtypes()
	Return a list of data type of each column




### A Full Use Case for Each Function:
```
Dataframe df

	         color       milleage	  automatic        price
	Toyota   "red"		 20.3		  true		 nullptr
	Honda    "black"	 41.0	      false		 20000
	Mazda	 "white"	 26.3		  true	 	 30000
	Subaru   "blue"	 	 17.8		  false		 25000

	df.get(0,1)
	-->  "black"

	df.get("price","Honda")
	-->  20000

	df.nrow()
	-->  4

	df.ncol()
	-->  4

	df.isnull()
	-->          color       milleage	  automatic    price
		Toyota   true		 true		  true		   false
		Honda    true	 	 true	      true		   true
		Mazda	 true	 	 true		  true	 	   true
		Subaru   true	 	 true		  true		   true

	df.notnull()
	-->          color       milleage	  automatic    price
		Toyota   false		 false		  false		   true
		Honda    false	 	 false	      false	       false
		Mazda	 false	 	 false		  false	       false
		Subaru   false	 	 false		  false	       false

	df.dropna()
	-->          color     	 milleage	  automatic    price
		Honda    "black"	 41.0	      false	       20000
		Mazda	 "white"	 26.3		  true	       30000
		Subaru   "blue"	 	 17.8		  false	       25000

	df.insert(3, "engine", [1,0,0,1])
	-->          color      milleage	automatic    engine price
		Toyota   "red"		20.3		true	     1      nullptr
		Honda    "black"	41.0	    false	     0      20000
		Mazda	 "white"	26.3		true	     0      30000
		Subaru   "blue"	 	17.8		false	     1      25000

	df.drop(3)
	--> 		 color       milleage	  automatic      
		Toyota   "red"		 20.3		  true		  
		Honda    "black"	 41.0	      false			
		Mazda	 "white"	 26.3		  true	 		
		Subaru   "blue"	 	 17.8		  false	

	df.drop("price")
	--> 		 color       milleage	  automatic      
		Toyota   "red"		 20.3		  true		  
		Honda    "black"	 41.0	      false			
		Mazda	 "white"	 26.3		  true	 		
		Subaru   "blue"	 	 17.8		  false	

	df.dtypes()
	-->  [String, float, bool, int]	
```
