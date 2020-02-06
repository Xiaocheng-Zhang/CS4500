Dataframe API description:
	Our dataframe supports int, float, bool, String Columns and potentially
	other types of data in column list format.

	The functions and its use cases are listed at following:

	- Dataframe df = new Dataframe(a,b,c,...)
		Dataframe constructor. The constructor can take one or more data columns.
		Columns can have different lengths. The shorter column will be filled 
		Null pointer at the end of column.

	- df.get(m,n)
		Return the value at row m and column n.
		The coordinates begins with row position, then followed by a comma, 
		and ends with the column position. 
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




A Full Use Case for Each Function:

	         color      milleage	automatic      price
	Toyota   "red"		 20.3		  true		  nullptr
	Honda    "black"	 41.0	      false			20000
	Mazda	 "white"	 26.3		  true	 		30000
	Subaru   "blue"	 	 17.8		  false			25000
