List_2D = [[1,2,3],[4,5,6],[7,8,9]] #List to be flattened
List_flat = []
for i in range(len(List_2D)): #Traversing through the main list
  for j in range (len(List_2D[i])): #Traversing through each sublist
    List_flat.append(List_2D[i][j]) #Appending elements into our flat_list
    
print("Original List:",List_2D)
print("Flattened List:",List_flat)