# Introduction of our implementation:

Our design include classes such as dataframe, row, rower, fielder, column, schema, etc.
Those classes are dependent each other.

# Overview of the design choices
For the implementation of column, row, schema and dataframe, we self created 
vec class to be used to represent column or any list data structure. 
We have vec in multiple data type such as String, char, int, bool, etc.


# use cases (the "examples" step from the design recipe)
```
Dataframe df

	         color      milleage	automatic      price
	Toyota   "red"		 20.3		  true		  nullptr
	Honda    "black"	 41.0	      false			20000
	Mazda	 "white"	 26.3		  true	 		30000
	Subaru   "blue"	 	 17.8		  false			25000

	df.get(0,1)
	-->  "black"

	df.get("price","Honda")
	-->  20000

	df.nrow()
	-->  4

	df.ncol()
	-->  4

	df.isnull()
	-->          color      milleage	automatic      price
		Toyota   true		 true		  true		   false
		Honda    true	 	 true	      true		    true
		Mazda	 true	 	 true		  true	 		true
		Subaru   true	 	 true		  true			true

	df.notnull()
	-->          color      milleage	automatic      price
		Toyota   false		 false		  false		    true
		Honda    false	 	 false	      false		    false
		Mazda	 false	 	 false		  false	 		false
		Subaru   false	 	 false		  false			false

	df.dropna()
	-->          color      milleage	automatic      price
		Honda    "black"	 41.0	      false			20000
		Mazda	 "white"	 26.3		  true	 		30000
		Subaru   "blue"	 	 17.8		  false			25000

	df.insert(3, "engine", [1,0,0,1])
	-->          color      milleage	automatic    engine   price
		Toyota   "red"		 20.3		  true		   1      nullptr
		Honda    "black"	 41.0	      false		   0      20000
		Mazda	 "white"	 26.3		  true	 	   0      30000
		Subaru   "blue"	 	 17.8		  false		   1      25000

	df.drop(3)
	--> 		 color      milleage	automatic      
		Toyota   "red"		 20.3		  true		  
		Honda    "black"	 41.0	      false			
		Mazda	 "white"	 26.3		  true	 		
		Subaru   "blue"	 	 17.8		  false	

	df.drop("price")
	--> 		 color      milleage	automatic      
		Toyota   "red"		 20.3		  true		  
		Honda    "black"	 41.0	      false			
		Mazda	 "white"	 26.3		  true	 		
		Subaru   "blue"	 	 17.8		  false	

	df.dtypes()
	-->  [String, float, bool, int]	
```
