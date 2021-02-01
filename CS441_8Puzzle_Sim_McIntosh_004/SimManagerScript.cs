using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System.Linq;
using UnityEngine.SceneManagement;


public class SimManagerScript : MonoBehaviour
{
    public float startInterval = 0f, endInterval = 0f;
    public int maxCalls = 10;
    public int heightLimit = 10;
    public int callCount = 0;
    public Camera theCam;
    public bool simulationStarted = false;
    public bool negOneNegOne = false;
    public int maxWidth = 40;
    public bool misplaced = false, manhattan = false, gaschnigs = false;
    public bool aStar = false, bestFirst = false;
    public bool isSolvable;
    public GameObject solvableText;
    public Text puzzleSolvedUIText, mainLimitReachedText, runTimeText, timedOutText, nodesVisitedText;
    public Button startButton;
    public GameObject theRootNode;
    public GameObject puzzleNodePrefab;
    MainMenuScript menuScript;
    PuzzleNodeScript rootsScript;
    int[,] puzzleMatrix;
    public List<GameObject> startingTiles = new List<GameObject>();
    Dictionary<int,List<int>> AvailableMovesDict;
    public Dictionary<Vector3, bool> occupiedTilePos;
    public List<GameObject> leafNodes = new List<GameObject>();
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
                if (!printedNodes.Contains(list)) {
                    Debug.Log("VISITEDNODES "+string.Join(", ", list));
                    printedNodes.Enqueue(list);
                }
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
        startInterval = Time.realtimeSinceStartup;
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
                bool solved = false;
                if (aStar) {
                    solved = AStarSearchExpandNodes(theRootNode);
                } else {
                    solved = BestFirstExpandNodes(theRootNode);    
                }
                // SOMETIMES ASTAR RETURNS FALSE WHEN IT SHOULDN'T
                // THIS EXTRA CHECK COMBS THROUGH THE VISITED LIST FOR THE GOAL
                solved = HaveWeVisited(goalList);
                // DISPLAYS THE RIGHT MESSAGE
                if (solved) {
                    StartCoroutine(DisplaypuzzleSolvedText());
                } else if (callCount >= maxCalls) {
                    DisplayMainLimitReachedText();
                } else {
                    DisplayTimedOutText();
                }
                endInterval = Time.realtimeSinceStartup; 
                runTimeText.color = new Color(255, 128, 0, 255);
                float totalTime = Mathf.Abs(startInterval - endInterval);
                runTimeText.text = totalTime.ToString("f3") + " seconds";
                int totalNodes = visitedNodes.Count;
                nodesVisitedText.text = totalNodes.ToString();
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
    public void DisplayTimedOutText()
    {
        timedOutText.color = new Color(255, 128, 0, 255);
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
        int myHeight = myPuzzleNode.Gn+1;
        List<int> spacingList = new List<int>(GetSpacing(maxSpacing, divisions, myHeight));
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
    public List<int> GetSpacing(int max, int divisions, int height)
    {
        List<int> XCoordPlacements = new List<int>();
        int spacings = (int) Mathf.Round(max / divisions);

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
    public bool IsThisSolved(PuzzleNodeScript theScript)
    {
        //Returns if this PuzzeNode matches the goal
        if (theScript.config.SequenceEqual(goalList)) {
            visitedNodes.Enqueue(goalList); //For debug printing
            return true;
        }
        return false;
    }
    /***
    True Best-First and A* Searching Pattern
    *- Pass in parent to AStar()
    *- Return true if Hn == 0
    *- Run parent makeChildren()
    *- Add parent to visitedNodes
    *- Make a list of all leafNodes in the entire tree
    *- Remove any visitedNode from leafNodes
    *- Get the leafNode with the lowest Fn  
    *- Pass that into AStar()
    */
    // This function expands the node
    public bool AStarSearchExpandNodes(GameObject parentNode)
    {
        if (!parentNode || callCount >= maxCalls)
            return false;
        callCount++; //THIS IS TO PREVENT STACK SMASHING
        // GRABS SCRIPT FOR PARENT NODE & CHECKS IF WE'VE VISITED
        PuzzleNodeScript parentScript = parentNode.GetComponent<PuzzleNodeScript>();
        // DOES THIS PARENT NODE SOLVE THE PUZZLE??
        if (IsThisSolved(parentScript))
            return true;
        // THIS IT JUST DOUBLE CHECKING NO LOOPS HAPPEN
        if (HaveWeVisited(parentScript.config))
            return false;
        // ADDING PARENT TO VISITEDNODES LIST
        visitedNodes.Enqueue(parentScript.config);
        // MAKES CHILDREN 
        MakeChildrenNodes(parentScript);
        // GETS A LIST OF ALL LEAFS IN THE TREE
        leafNodes = new List<GameObject>();
        GetAllLeafNodes(theRootNode);
        // REMOVES THE LEAF NODES THAT WE'VE VISITED
        RemoveVisitedNodes();        
        GameObject lowestFnNode = GetLeafWithLowestFn();
        if (!lowestFnNode)  //I really don't see this happening.
            return false;
        AStarSearchExpandNodes(lowestFnNode);
        return false;
    }
    public bool BestFirstExpandNodes(GameObject parentNode)
    {
        if (!parentNode || callCount >= maxCalls)
            return false;
        callCount++; //THIS IS TO PREVENT STACK SMASHING
        // GRABS SCRIPT FOR PARENT NODE & CHECKS IF WE'VE VISITED
        PuzzleNodeScript parentScript = parentNode.GetComponent<PuzzleNodeScript>();
        // DOES THIS PARENT NODE SOLVE THE PUZZLE??
        if (IsThisSolved(parentScript))
            return true;
        // THIS IT JUST DOUBLE CHECKING NO LOOPS HAPPEN
        if (HaveWeVisited(parentScript.config))
            return false;
        // ADDING PARENT TO VISITEDNODES LIST
        visitedNodes.Enqueue(parentScript.config);
        // MAKES CHILDREN 
        MakeChildrenNodes(parentScript);
        // GETS A LIST OF ALL LEAFS IN THE TREE
        leafNodes = new List<GameObject>();
        GetAllLeafNodes(theRootNode);
        // REMOVES THE LEAF NODES THAT WE'VE VISITED
        RemoveVisitedNodes();        
        GameObject lowestHnNode = GetLeafWithLowestHn();
        if (!lowestHnNode)  //I really don't see this happening.
            return false;
        BestFirstExpandNodes(lowestHnNode);
        return false;
    }
    public void RemoveVisitedNodes()
    {
        // WE'RE HAVING ISSUES NOT REMOVING ALL DUPLICATES. COPYING LIST.
        for (int i = 0; i < leafNodes.Count; ++i) {
            if (leafNodes[i] != null) {
                PuzzleNodeScript script = leafNodes[i].GetComponent<PuzzleNodeScript>();
                if (HaveWeVisited(script.config)) {     //Checks that with the memorization list
                    Debug.Log("\t\tREMOVING = "+string.Join(", ",script.config));
                    leafNodes.RemoveAt(i); //Removes if we've been there
                    --i;
                }
            }
        }
    }
    public void GetAllLeafNodes(GameObject parentNode)
    {
        if (!parentNode)
            return;
        PuzzleNodeScript script = parentNode.GetComponent<PuzzleNodeScript>();
        for (int i = 0; i < script.next.Count; ++i) {
            GetAllLeafNodes(script.next[i]);
        }
        // THIS MEANS YOU'RE A LEAF, ADD IT!
        if (script.next.Count <= 0)
            leafNodes.Add(parentNode); 
        return;
    }
    public bool HaveWeVisited(int[] myList)
    {
        if (visitedNodes.Count > 0)
            foreach (int[] list in visitedNodes)
                if (list.SequenceEqual(myList))
                    return true;
        return false;
    }
    public GameObject GetLeafWithLowestFn()
    {
        if (leafNodes.Count <= 0) return null;
        PuzzleNodeScript lowestFnNode = leafNodes[0].GetComponent<PuzzleNodeScript>();
        for (int i = 1; i < leafNodes.Count; ++i) {
            PuzzleNodeScript nextNode = leafNodes[i].GetComponent<PuzzleNodeScript>();
            if (nextNode.Fn < lowestFnNode.Fn) {
                lowestFnNode = nextNode;
            }
        }
        Debug.Log("\tLOWESTFN = "+string.Join(", ",lowestFnNode.config));
        return lowestFnNode.gameObject;
    }
    public GameObject GetLeafWithLowestHn()
    {
        if (leafNodes.Count <= 0) return null;
        PuzzleNodeScript lowestHnNode = leafNodes[0].GetComponent<PuzzleNodeScript>();
        for (int i = 1; i < leafNodes.Count; ++i) {
            PuzzleNodeScript nextNode = leafNodes[i].GetComponent<PuzzleNodeScript>();
            if (nextNode.Hn < lowestHnNode.Hn) {
                lowestHnNode = nextNode;
            }
        }
        Debug.Log("\tLOWESTHN = "+string.Join(", ",lowestHnNode.config));
        return lowestHnNode.gameObject;
    }
    public void UpdateMaxNodeAmount(string userInput)
    {
        maxCalls = (int) Mathf.Round(int.Parse(userInput));
    }
    public void UpdateHeightLimit(string userInput)
    {
        heightLimit = (int) Mathf.Round(int.Parse(userInput));
    }
    public void UpdateCameraMovement()
    {
        float speed = 10.0f;
        Vector3 camPos = theCam.transform.position;
        if (Input.GetKey(KeyCode.Space))
            speed = 20.0f;
        else
            speed = 10.0f;

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
