using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System.Linq;
using UnityEngine.SceneManagement;


public class SimManagerScript : MonoBehaviour
{
    public int maxCalls = 10;
    public int callCount = 0;
    public Camera theCam;
    public bool simulationStarted = false;
    public bool negOneNegOne = false;
    public int maxWidth = 40;
    public bool misplaced = false, manhattan = false, gaschnigs = false;
    public bool aStar = false, bestFirst = false;
    public bool isSolvable;
    public GameObject solvableText;
    public Text puzzleSolvedUIText, mainLimitReachedText;
    public Button startButton;
    public GameObject theRootNode;
    public GameObject puzzleNodePrefab;
    MainMenuScript menuScript;
    PuzzleNodeScript rootsScript;
    int[,] puzzleMatrix;
    public List<GameObject> startingTiles = new List<GameObject>();
    Dictionary<int,List<int>> AvailableMovesDict;
    public Dictionary<Vector3, bool> occupiedTilePos;
    public Queue<int[]> visitedNodes = new Queue<int[]>(); 
    public Queue<int[]> printedNodes = new Queue<int[]>(); 
    int[] goalList = new int[]{1, 2, 3, 4, 5, 6, 7, 8, 0};
    int[,] goalMatrix = new int[,] {
        {1, 2, 3,},
        {4, 5, 6,},
        {7, 8, 0,}
    };
    Dictionary<int,Vector3> ThreeByThreeLocs = new Dictionary<int,Vector3>() {
        { 0, new Vector3(-1, 1,0) },
        { 1, new Vector3( 0, 1,0) },
        { 2, new Vector3( 1, 1,0) },
        { 3, new Vector3(-1, 0,0) },
        { 4, new Vector3( 0, 0,0) },
        { 5, new Vector3( 1, 0,0) },
        { 6, new Vector3(-1,-1,0) },
        { 7, new Vector3( 0,-1,0) },
        { 8, new Vector3( 1,-1,0) }
    };
    void Start()
    {
        rootsScript = theRootNode.GetComponent<PuzzleNodeScript>();
        solvableText.SetActive(false);
        InitOccupiedLocDict();
    }
    public bool[] isOccupied = new bool[9];
    // Checks if all starting tiles are placed.
    // Once they are, this update will no longer call ReadyToGo()
    void Update()
    {
        if (simulationStarted){
            if (theCam.orthographic == true)
                theCam.orthographic = false;
            UpdateCameraMovement();
        }
        if (startButton.interactable == false) {
            UpdateOccupiedLocations();
            if (ReadyToGo()) {
                startButton.interactable = true;
            } else {
                startButton.interactable = false;
            }
        }
        if(Input.GetKeyDown(KeyCode.R)){
            Scene scene = SceneManager.GetActiveScene();
            SceneManager.LoadScene(scene.name);
        }
        if (visitedNodes.Count > 0) {
            foreach (int[] list in visitedNodes) {
                //if (!printedNodes.Contains(list)) {
                    Debug.Log("VISITEDNODES "+string.Join(", ", list));
               //     printedNodes.Enqueue(list);
               // }
            }
        }

    }
    public bool ReadyToGo()
    {
        for (int i = 0; i < 8; ++i) {
            if (startingTiles[i] != null) {
                TileScript theTile = startingTiles[i].GetComponent<TileScript>();
                if (!theTile.isReady) {
                    return false;
                }
            }
        }
        return true;
    }
    //This function combs through the list of number Tiles,
    // and tries to find any that share the same coordinates
    // as the initial root board node. If they do, mark those
    // specific coordinates as "occupied" which prevents number
    // tiles from being stacked on each other at setup.
    public void UpdateOccupiedLocations()
    {
        for (int i = 0; i < 9; ++i) {
            Vector3 pos = ThreeByThreeLocs[i];
            occupiedTilePos[pos] = FreeUpPos(pos);
        } 
        UpdateOccupiedList();
    }
    //This checks for each startingTile, and compares it with
    // each position on the 3x3 rootboard. If the position is
    // vacant, then the boolean in the dictionary is marked false;
    public bool FreeUpPos(Vector3 occupiedLoc)
    {
        for (int i = 0; i < 8; ++i) {
            if (startingTiles[i] != null) {
                Vector3 thisPos = startingTiles[i].transform.position;
                if (thisPos == occupiedLoc) {
                    return true;
                }
            }
        }
        return false;
    }

    public void StartSim(MainMenuScript theMenuScript)
    {
        menuScript = theMenuScript;
        rootsScript.RootMakeConfigList();
        if (!InitConfigIsSolvable()) {
            menuScript.GoBack();
            StartCoroutine(DisplayNotSolvableText());
        } else {
            Update_H_Vals(rootsScript);
            // Checks to see if initial puzzle setup is solved
            if (rootsScript.config.SequenceEqual(goalList)) {
                StartCoroutine(DisplaypuzzleSolvedText());
            } else {
                simulationStarted = true;
                // RECURSIVE FUNCTIONS TO FIND THE NODE
                if (aStar) {
                    AStarSearchExpandNodes(theRootNode);
                } else {
                    BestFirstExpandNodes(theRootNode);    
                }
                // DISPLAYS THE RIGHT MESSAGE
                if (callCount >= maxCalls)
                    DisplayMainLimitReachedText();
                else
                    StartCoroutine(DisplaypuzzleSolvedText());
            }
        }
    }
    // Returns true if the number of conversions is even
    public bool InitConfigIsSolvable()
    {
        List<int> rootsListOmittingZero = new List<int>();
        for (int i = 0; i < 9; ++i)
            if (rootsScript.config[i] != 0)
                rootsListOmittingZero.Add(rootsScript.config[i]);
        int inversionCount = InversionCount(rootsListOmittingZero);
        if (inversionCount %2 == 0)
            return true;
        return false;
    }
    //Once a new temporary list is created with zero omitted,
    // we can check if the list is solvable
    public int InversionCount(List<int> myList)
    {
        int inversionCount = 0;
        for (int i = 0; i < 7; ++i) {
            for (int j = i+1; j < 8; ++j) {
                if (myList[i] > myList[j]) {
                    inversionCount++;
                }
            }
        }
        return inversionCount;
    }
    public IEnumerator DisplayNotSolvableText()
    {
        solvableText.SetActive(true);  
        yield return new WaitForSeconds(5f);
        solvableText.SetActive(false);
    }
    public IEnumerator DisplaypuzzleSolvedText()
    {
        puzzleSolvedUIText.color = new Color(255, 128, 0, 255);
        yield return new WaitForSeconds(7f);
        puzzleSolvedUIText.color = new Color(255, 128, 0, 10);
        yield return null;
    }
    public void DisplayMainLimitReachedText()
    {
        mainLimitReachedText.color = new Color(255, 128, 0, 255);
    }
    public void SetMisplaced()
    {
        misplaced = true;
        manhattan = false;
        gaschnigs = false;
    }
    public void SetManhattan()
    {
        misplaced = false;
        manhattan = true;
        gaschnigs = false;
    }
    public void SetGashnigs()
    {
        misplaced = false;
        manhattan = false;
        gaschnigs = true;
    }
    public void SetAStar()
    {
        aStar = true;
        bestFirst = false;
    }
    public void SetBestFirst()
    {
        aStar = false;
        bestFirst = true;
    }
    public void Update_H_Vals(PuzzleNodeScript puzzleNode)
    {
        int HValText = 0;
        if (misplaced) {
            HValText = CountMisplacedTiles(puzzleNode.config);
        } else if (manhattan) {
            HValText = CountManhattanDistance(puzzleNode.config);
        } else {
            HValText = CountGaschnigsSwaps(puzzleNode.config);
        }
        puzzleNode.UpdateHVal(HValText);
    }
    public int CountMisplacedTiles(int[] myList)
    {
        int count = 0;
        for (int i = 0; i < 9; ++i) {
            if (myList[i] != goalList[i]) {
                if (myList[i] > 0) {
                    count++;
                }
            }
        }
        return count;
    }
    // Counts the x and y coordinate differences of a single value
    // shared between the current and goal configurations.
    // Notice the number zero is omitted here.
    public int CountManhattanDistance(int[] myList)
    {
        int count = 0;
        ConvertListToMatrix(myList);
        for (int i = 1; i < 9; ++i) {
            int[] puzzleMatIndexes = GetXYIndex(puzzleMatrix, i);
            int[] goalMatIndexes = GetXYIndex(goalMatrix, i);
            count += Mathf.Abs(puzzleMatIndexes[0]-goalMatIndexes[0]);
            count += Mathf.Abs(puzzleMatIndexes[1]-goalMatIndexes[1]);
        }
        return count;
    }
    public int CountGaschnigsSwaps(int[] myList)
    {
        int[] tempList = new int[9];
        for (int i = 0; i < 9; ++i)
            tempList[i] = myList[i];
        int count = 0, breakout = 0;
        while (!tempList.SequenceEqual(goalList) || breakout < 100) {
            for (int i = 0; i < 8; ++i) {
                if (tempList[i] == 0) {
                    int desiredVal = i+1;
                    int new_zero_loc = FindIndexOf(tempList, desiredVal);
                    tempList[new_zero_loc] = 0;
                    tempList[i] = desiredVal;
                    count++;
                }
            }
            breakout++;
        }
        return count;
    }
    public void ConvertListToMatrix(int[] myList)
    {
        puzzleMatrix = new int[,] {
            {myList[0], myList[1], myList[2],},
            {myList[3], myList[4], myList[5],},
            {myList[6], myList[7], myList[8],}
        };    
    }
    public int[] GetXYIndex(int[,] matrix, int val)
    {
       int[] indexes = new int[] {0,0}; 
       for (int i = 0; i < 3; ++i) {
           for (int j = 0; j < 3; ++j) {
                if (matrix[i,j].Equals(val)) {
                    indexes[0] = i;
                    indexes[1] = j;
                }
            }
        }
        return indexes;
    }
    public int FindIndexOf(int[] theList, int theVal)
    {
        //Debug.Log("FINDINDEXOF()"+string.Join(", ", theList));
        for (int i = 0; i < 9; ++i)
            if (theList[i] == theVal)
                return i;
        return -1;
    }
    public void MakeChildrenNodes(PuzzleNodeScript myPuzzleNode)
    {
        AvailableMovesDict = new Dictionary<int,List<int>>() {
            { 0 , new List<int>() {1, 3} },
            { 1 , new List<int>() {0, 2, 4} },
            { 2 , new List<int>() {1, 5} },
            { 3 , new List<int>() {0, 4, 6} },
            { 4 , new List<int>() {1, 3, 5, 7} },
            { 5 , new List<int>() {2, 4, 8} },
            { 6 , new List<int>() {3, 7} },
            { 7 , new List<int>() {4, 6, 8} },
            { 8 , new List<int>() {7, 5} }
        };
        //Debug.Log("MAKE CHILDREN()"+string.Join(", ", myPuzzleNode.config));
        //Finds the zero location, passes that in as the argument along with the list
        int zerosIndex = FindIndexOf(myPuzzleNode.config, 0);        
        List<int> nextMoves = new List<int>(AvailableMovesDict[zerosIndex]);
        Queue<int[]> listOfNextMoves = new Queue<int[]>(CreateQueueOfNextMoves(myPuzzleNode.config, nextMoves));
        //This pads out the nodes so they don't clutter
        int maxSpacing = maxWidth / (myPuzzleNode.Gn+1);
        int divisions = listOfNextMoves.Count;
        List<int> spacingList = new List<int>(GetSpacing(maxSpacing, divisions));
        //This goes through each new puzzleNode and connects them to their parent
        int i = 0;
        //This makes nodes, might be good to make a new function?
        while (listOfNextMoves.Count != 0) {
            int[] listToAddForNewPuzzleNode = listOfNextMoves.Dequeue();
            GameObject theNewPuzzleNode = Instantiate(puzzleNodePrefab, myPuzzleNode.transform.position, Quaternion.identity) as GameObject;
            theNewPuzzleNode.transform.parent = myPuzzleNode.transform;
            Vector3 placement = new Vector3(myPuzzleNode.transform.position.x+spacingList[i], myPuzzleNode.transform.position.y-5, 1);
            theNewPuzzleNode.transform.position = placement;
            UpdateNewNodeStuff(theNewPuzzleNode, myPuzzleNode, listToAddForNewPuzzleNode, i);
            i++;
        }
        myPuzzleNode.IMadeChildren = true;
    }
    public void UpdateNewNodeStuff(GameObject childNode, PuzzleNodeScript parentNode, int[] newConfigList, int i)
    {
        DrawNodeLine(parentNode.gameObject, childNode.gameObject);
        parentNode.next.Add(childNode);
        PuzzleNodeScript childNodeScript = parentNode.next[i].GetComponent<PuzzleNodeScript>();
        childNodeScript.SetGVal(parentNode.Gn+1);
        childNodeScript.SetUpConfig(newConfigList);
        Update_H_Vals(childNodeScript);
        childNodeScript.SetupTilePosDict();
        childNodeScript.SetUpTiles();
    }
    //Creates a queue of the next moves available, based on where the zero is
    public Queue<int[]> CreateQueueOfNextMoves(int[] myList, List<int> nextMoves)
    {
        //Debug.Log("MYLIST IN CREATED QUEUE "+string.Join(", ", myList));
        int zerosIndex = FindIndexOf(myList, 0);        
        Queue<int[]> movesQueue = new Queue<int[]>();
        for (int i = 0; i < nextMoves.Count; ++i) {
            int[] listToAdd = new int[9];
            //Copies over myList to the new temp list to add to the queue, after configuration
            for (int j = 0; j < 9; ++j)
                listToAdd[j] = myList[j];
            int desiredVal = listToAdd[nextMoves[i]];
            listToAdd[zerosIndex] = desiredVal;
            listToAdd[nextMoves[i]] = 0;
            movesQueue.Enqueue(listToAdd);
        }
        return movesQueue;
    }
    public void DrawNodeLine(GameObject nodeOne, GameObject nodeTwo)
    {
        LineRenderer line = nodeTwo.gameObject.AddComponent<LineRenderer>();
        line.material = new Material(Shader.Find("Sprites/Default"));
        line.startWidth = 0.05f;
        line.endWidth = 0.05f;
        line.positionCount = 2;
        line.SetPosition(0, nodeTwo.transform.position);
        line.SetPosition(1, nodeOne.transform.position);
    }
    public List<int> GetSpacing(int max, int divisions)
    {
        List<int> XCoordPlacements = new List<int>();
        int spacings = max / divisions;
        if (spacings < 6)
            spacings = 6;
        if (divisions == 2) {
            XCoordPlacements.Add(spacings*-1);
            XCoordPlacements.Add(spacings);
        } else if (divisions == 3) {
            XCoordPlacements.Add(spacings*-1);
            XCoordPlacements.Add(0);
            XCoordPlacements.Add(spacings);
        } else if (divisions == 4) {
            XCoordPlacements.Add(spacings*-2);
            XCoordPlacements.Add(spacings*-1);
            XCoordPlacements.Add(spacings);
            XCoordPlacements.Add(spacings*2);
        }
        return XCoordPlacements;
    }
    public bool LookForSolvedPuzzle(GameObject myPuzzleNode)
    {
        if (!myPuzzleNode)
            return false;
        //Gets the PuzzleNode's script
        PuzzleNodeScript theScript = myPuzzleNode.GetComponent<PuzzleNodeScript>();
        //Returns if this PuzzeNode matches the goal
        if (theScript.config.SequenceEqual(goalList)) {
            visitedNodes.Enqueue(goalList);
            return true;
        }
        //Otherwise it combs through the next pointers recursively
        for (int i = 0; i < theScript.next.Count; ++i) {
            if (LookForSolvedPuzzle(theScript.next[i].gameObject))
                return true;
        }
        return false;
    }
    // This function expands the node
    public bool AStarSearchExpandNodes(GameObject parentNode)
    {
        if (!parentNode || callCount >= maxCalls)
            return false;
        // Grabs the info for the node. Checks if we've visited it.
        PuzzleNodeScript parentScript = parentNode.GetComponent<PuzzleNodeScript>();
        if (visitedNodes.Contains(parentScript.config))
            return false;
        // Since the above check isn't working, I'm doing it myself!
        if (visitedNodes.Count > 0)
            foreach (int[] list in visitedNodes)
                if (list.SequenceEqual(parentScript.config))
                    return false;
        visitedNodes.Enqueue(parentScript.config);
        MakeChildrenNodes(parentScript);
        //Looks for a solution in the currently made puzzle. if it's done we break.
        if (LookForSolvedPuzzle(parentNode))
            return true;
        // GET A LIST OF ALL CHILDREN THAT WE HADN'T VISITED, COPIES PARENT REMOVES ALL VISITED NODES
        List<GameObject> unvisitedNodes = new List<GameObject>(parentScript.next);
        foreach (GameObject checkNode in parentScript.next) {   //Combs through unedited parent list because 
            PuzzleNodeScript nodeScript = checkNode.GetComponent<PuzzleNodeScript>();
            if (visitedNodes.Contains(nodeScript.config)) {     //Checks that with the memorization list
                unvisitedNodes.Remove(checkNode);               //Removes if we've been there
            } else {
                if (unvisitedNodes.Count <= 0) {             //If we've been to all children, Break!
                    return false;
                }
            }
        }
        // PRIORITIZES THE REMAINING NODES IN THE UNVISITED LIST (Bubble sort)
        for (int i = 0; i < unvisitedNodes.Count-1; ++i) {
            PuzzleNodeScript leftChildScript = unvisitedNodes[i].GetComponent<PuzzleNodeScript>();
            for (int j = i+1; j < unvisitedNodes.Count; ++j) {
                PuzzleNodeScript rightChildScript = unvisitedNodes[j].GetComponent<PuzzleNodeScript>();
                if (rightChildScript.Fn < leftChildScript.Fn) {
                    GameObject tempChild = unvisitedNodes[i];
                    unvisitedNodes[i] = unvisitedNodes[j];
                    unvisitedNodes[j] = tempChild;
                }
            }
        }
        callCount++;
        // Calls this function recursively for each child
        for (int i = 0; i < unvisitedNodes.Count; ++i) {
            if (AStarSearchExpandNodes(unvisitedNodes[i]))
                return true;
        }
        return false;
    }
/*
    // This function expands the node
    public bool AStarSearchExpandNodes(GameObject myPuzzleNode)
    {
        if (!myPuzzleNode || callCount >= maxCalls)
            return false;
        // Grabs the info for the node. Checks if we've visited it.
        PuzzleNodeScript parentScript = myPuzzleNode.GetComponent<PuzzleNodeScript>();
        if (!visitedNodes.Contains(parentScript.config) && !parentScript.IMadeChildren) {
            visitedNodes.Enqueue(parentScript.config);
            MakeChildrenNodes(parentScript);
        }
        //Prints stuff!
        Debug.Log("ENQUEUEING\t\t"+string.Join(", ", parentScript.config)+"\tAT\t"+parentNode.transform.position.ToString());
        Debug.Log("THERE ARE "+visitedNodes.Count.ToString()+" LISTS IN VISITED NODES:");
        if (visitedNodes.Count > 0) {
            foreach (int[] list in visitedNodes) {
                Debug.Log("\tVISITEDNODES\t"+string.Join(", ", list));
            }
        }
        //Looks for a solution in the currently made puzzle. if it's done we break.
        if (LookForSolvedPuzzle(myPuzzleNode))
            return true;
        // GET A LIST OF ALL CHILDREN THAT WE HADN'T BEEN TO, THEN GET THE ONE WITH THE SMALLEST Fn
        //Find the child with the lowest Fn, initialized to the first child
        PuzzleNodeScript lowestFnChildScript = parentScript.next[0].GetComponent<PuzzleNodeScript>();
        //If we've been there, it initializes to the next one we hadn't been to
        int myIterator = 0;
        if (visitedNodes.Contains(lowestFnChildScript.config)) {    //This checks the memorization list
            for (int i = 1; i < parentScript.next.Count; ++i) {     //Index 1 through all of the children nodes
                PuzzleNodeScript compareChildScript = parentScript.next[i].GetComponent<PuzzleNodeScript>(); 
                if (!visitedNodes.Contains(compareChildScript.config)) {    //Checks that with the memorization list
                    lowestFnChildScript = parentScript.next[i].GetComponent<PuzzleNodeScript>();
                    myIterator = i;
                    break;
                } else {
                //If we've been to all children, break!
                    if (i == parentScript.next.Count) {
                        return false;
                    }
                }
            }
        }
        //Combs through the rest of the children, saving the child with the loweset Fn
        //Doesn't save the child if we've already been to that node
        for (int i = myIterator; i < parentScript.next.Count; ++i ) {
            PuzzleNodeScript compareChildsScript = parentScript.next[i].GetComponent<PuzzleNodeScript>();
            //If the next value is lower and we hadn't been there, update to that node
            if (compareChildsScript.Fn <= lowestFnChildScript.Fn) {
                if (!visitedNodes.Contains(compareChildsScript.config)) {
                    lowestFnChildScript = parentScript.next[i].GetComponent<PuzzleNodeScript>();
                }
            }
        }
        callCount++;
        return AStarSearchExpandNodes(lowestFnChildScript.gameObject);
    }
*/
    // This search ignores Gn in only looking for Hn which includes 
    public bool BestFirstExpandNodes(GameObject myPuzzleNode)
    {
        if (!myPuzzleNode || callCount >= maxCalls)
            return false;
        PuzzleNodeScript parentScript = myPuzzleNode.GetComponent<PuzzleNodeScript>();
        //Setup only the nodes that need it
        if (!parentScript.IMadeChildren)
            MakeChildrenNodes(parentScript);
        //Looks for a solution in the currently made puzzle
        if (LookForSolvedPuzzle(myPuzzleNode))
            return true;
        //Find the child with the lowest Hn, initialized to the first child
        PuzzleNodeScript lowestHnChildScript = parentScript.next[0].GetComponent<PuzzleNodeScript>();
        //Combs through the rest of the children, saving the child with the loweset Hn
        for (int i = 1; i < parentScript.next.Count; ++i ) {
            PuzzleNodeScript compareChildsScript = parentScript.next[i].GetComponent<PuzzleNodeScript>();
            if (compareChildsScript.Hn < lowestHnChildScript.Hn) {
                lowestHnChildScript = parentScript.next[i].GetComponent<PuzzleNodeScript>();
            }
        }
        callCount++;
        return BestFirstExpandNodes(lowestHnChildScript.gameObject);
    }
    public void UpdateCameraMovement()
    {
        float speed = 10.0f;
        Vector3 camPos = theCam.transform.position;
        if (Input.GetKey(KeyCode.UpArrow))
        {
            camPos.y += speed * Time.deltaTime;
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            camPos.y -= speed * Time.deltaTime;
        }
        if (Input.GetKey(KeyCode.RightArrow))
        {
            camPos.x += speed * Time.deltaTime;
        }
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            camPos.x -= speed * Time.deltaTime;
        }
        if (Input.GetKey(KeyCode.Q))
        {
            camPos.z += speed * Time.deltaTime;
        }
        if (Input.GetKey(KeyCode.A))
        {
            camPos.z -= speed * Time.deltaTime;
        }
        theCam.transform.position = camPos;
    }
    public void InitOccupiedLocDict()
    {
        occupiedTilePos = new Dictionary<Vector3, bool>() {
            { new Vector3(theRootNode.transform.position.x-1,theRootNode.transform.position.y+1, 0), false},
            { new Vector3(theRootNode.transform.position.x+0,theRootNode.transform.position.y+1, 0), false},
            { new Vector3(theRootNode.transform.position.x+1,theRootNode.transform.position.y+1, 0), false},
            { new Vector3(theRootNode.transform.position.x-1,theRootNode.transform.position.y+0, 0), false},
            { new Vector3(theRootNode.transform.position.x+0,theRootNode.transform.position.y+0, 0), false},
            { new Vector3(theRootNode.transform.position.x+1,theRootNode.transform.position.y+0, 0), false},
            { new Vector3(theRootNode.transform.position.x-1,theRootNode.transform.position.y-1, 0), false},
            { new Vector3(theRootNode.transform.position.x+0,theRootNode.transform.position.y-1, 0), false},
            { new Vector3(theRootNode.transform.position.x+1,theRootNode.transform.position.y-1, 0), false}
        };
    }
    public void UpdateOccupiedList()
    {
        isOccupied[0] = occupiedTilePos[new Vector3(-1, 1,0)];
        isOccupied[1] = occupiedTilePos[new Vector3( 0, 1,0)];
        isOccupied[2] = occupiedTilePos[new Vector3( 1, 1,0)];
        isOccupied[3] = occupiedTilePos[new Vector3(-1, 0,0)];
        isOccupied[4] = occupiedTilePos[new Vector3( 0, 0,0)];
        isOccupied[5] = occupiedTilePos[new Vector3( 1, 0,0)];
        isOccupied[6] = occupiedTilePos[new Vector3(-1,-1,0)];
        isOccupied[7] = occupiedTilePos[new Vector3( 0,-1,0)];
        isOccupied[8] = occupiedTilePos[new Vector3( 1,-1,0)];
    }
}
