using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System;
using Random=UnityEngine.Random;


public class BoardManagerScript : MonoBehaviour
{
    public int didntMakeAChoice = 0;
    public bool goodToGo = false;
    public Text clashesText;
    string theHighestString;
    int theHighestScore = 0;
    public string[] populationStrings;
    public int[] populationScores;
    public float[] populationPercentages;
    public float[,] populationProportions;
    public string[] selectedParentsStrings;
    public string[] childrenStrings;
    public int numPoplation, numIterations, currentIteration;
    public float mutationPct;
    public GameObject prefabTile;
    public GameObject theCanvas;
    public GameObject theBoard;
    public GameObject theChart;
    ChartScript theChartScript;
    GameObject [,] myTileList = new GameObject[8,8];
    public InputField initPopInput, numIterationInput, mutationPctInput;
    public Button GoButton;
    // Start is called before the first frame update
    void Start()
    {
        theChartScript = theChart.GetComponent<ChartScript>();
        CreateBoard();
    }
    // Update is called once per frame
    void Update()
    {
        theChartScript.SetNumPop(numIterations);
        if (goodToGo){
            goodToGo = false;
            DisableButtons();
            CreateInitialGeneration();
            while (currentIteration < numIterations) {
                GetFitness();
                SelectParents();
                CrossOver();
                MutateChildren();
                GetTheBest();
                MakeNewGeneration();
                UpdateChart();
                ++currentIteration;
            }
            PlaceQueens(theHighestString);
            int highFitScore = CalculateClashes(theHighestString);
            UpdateClashesText(highFitScore);
        }
        if(Input.GetKeyDown(KeyCode.R))
        {
            SceneManager.LoadScene(0);
        }
    }
    public void CreateBoard()
    {
        int count = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Vector2 boardSpot = theBoard.transform.position;
                Vector2 myPos = new Vector2(boardSpot.x + (i * 50)+25, boardSpot.y + (j * 50)+25);
                myTileList[i,j] = Instantiate(prefabTile, myPos, Quaternion.identity);
                myTileList[i,j].transform.SetParent(theBoard.transform, true);
                TileScript tileScript = myTileList[i,j].GetComponent<TileScript>();
                tileScript.UpdateMyText(i.ToString() + "," + j.ToString());
                tileScript.UpdateMyBackGround(count);
                count++;
            }
            count++;
        }
    }
    /* PLACEQUEENS()
        //Marks the board spots as "QUEEN" for the optimal solution
        "12345678"
        pos = 8-1 = 7
        myTileList[7,7] = "QUEEN"
        "1234567"
        pos = 7-1 = 6
        myTileList[6,6] = "QUEEN"
    */
    public void PlaceQueens(string highScoreString)
    {
        //Debug.Log("TheConfig = "+theConfig);
        int myConfig = int.Parse(highScoreString);
        for (int i = 7; i >= 0; i--) {
            int pos = myConfig % 10;
            //Debug.Log("Pos = "+pos.ToString());
            TileScript tileScript = myTileList[i,pos-1].GetComponent<TileScript>();
            tileScript.UpdateMyText("QUEEN");
            myConfig /= 10;
        }
    }
    //Since strings represent each column individually,
    // only row clashes are considered along with diagnonal
    public int CalculateClashes(string theConfig)
    {
        int clashes = RowClashes(theConfig);
        clashes += DiagonalClashes(theConfig);
        return clashes;
    }
    //This only looks for horizontal (row) clashes.
    //It starts with the leftmost Queen (element in the string),
    // and looks at that same row for another Queen to the right.
    public int RowClashes(string theConfig)
    {
        int rowClashes = 0;
        for (int i = 0; i < 8-1; i++) {
            for (int j = i+1; j < 8; j++) {
                // Apparently, it's a pain to convert a Char to an Int in C#
                int firstNum = (int) char.GetNumericValue(theConfig[i]);
                int nextNum = (int) char.GetNumericValue(theConfig[j]);
                //Debug.Log("FirstNum = "+firstNum.ToString());
                if (firstNum == nextNum)
                    rowClashes++;
            }
        }
        return rowClashes;
    }
    //DiagonalClashes calls an overload for each diagonal attack path
    //Since we're combing through the string from left to right, 
    // we do not need to conider the SE and SW attack directions,
    // which in considering them in our totals will only double the results.
    public int DiagonalClashes(string theConfig)
    {
        int diagClashes = 0;
        // Loops through each character in the configuration string
        for (int i = 0; i < 8; i++) {
            int j = (int) char.GetNumericValue(theConfig[i]);
            diagClashes += DiagonalClashes(i, j-1,  1,  1, theConfig);     //NE
            diagClashes += DiagonalClashes(i, j-1, -1,  1, theConfig);     //NW
        }
        return diagClashes;
    }
    //Xcor and Ycor arguments are the coordinates of the Queen we are exmaining from
    //The rest of the board is examined on the NW and NW attack paths
    // starting from the Queen coordinates in the arguments.
    //"theConfig" is holds the information about the other Queens on the board.
    //For each column (element) in theConfig string, we look to the remaining board rightward.
    //The x coordinate increases by 1 along with the y coordinate increasing by 1, too.
    //As those values increase, the incrementing x is placed as the element check into the string,
    // if the result of that value is the same as incrementing y, then there is a clash.
    public int DiagonalClashes(int Xcor, int Ycor, int Xdir, int Ydir, string theConfig)
    {
        int diagClashes = 0;
        // Double conditional for loop, increases in the direction from the arguments
        for (int x=Xcor+Xdir, y=Ycor+Ydir; x <= 7 && x >= 0 && y <= 7 && y >= 0; x+=Xdir, y+=Ydir) {
            if (y == ((int) char.GetNumericValue(theConfig[x]))-1)
                diagClashes++;
        }
        return diagClashes;
    }
    //This updates the optimal solutions "Clashes" amount
    public void UpdateClashesText(int highScore)
    {
        clashesText.text = (highScore).ToString();
    }
    //This receives input from the user and updates numPopulation.
    //If a non-numerical value is entered,
    // then the START button can't be clicked.
    //An even number is required since pairs of children are cross
    // examined in the CrossOver() function. If the input from the user
    // is an odd number then this simply adds one and doesn't tell the user.
    public void UpdateNumPopulation(string newPop)
    {
        if(int.TryParse(newPop, out numPoplation)) {
            if(numPoplation %2 != 0) {
                numPoplation++;
            }
            GoButton.interactable = true;
        } else {
            GoButton.interactable = false;
        }
    }
    //Takes input from the user, if the input is non-numerical,
    // then the START button cannot be clicked
    //NumIterations is the number of generations.
    public void UpdateNumIterations(string newIterations)
    {
        if(int.TryParse(newIterations, out numIterations))
            GoButton.interactable = true;
        else
            GoButton.interactable = false;
    }
    //Takes input from the user, if the input is non-numerical,
    // then the START button cannot be clicked
    //MutationsPct decides whether a string will be
    // mutated or not.
    public void UpdateMutationPctn(string newPct)
    {
        if(float.TryParse(newPct, out mutationPct))
            GoButton.interactable = true;
        else
            GoButton.interactable = false;
    }
    //Start button pressed
    public void GoodToGo()
    {
        goodToGo = true;
    }
    //Creates the inital generation to start with.
    //These are strings with each element randomly
    // selected between 1-8. I chose to do this for legibility.
    //1 is actually the first, bottommost row on the board,
    // while 8 is the highest.
    public void CreateInitialGeneration()
    {
        populationStrings = new string [numPoplation];
        /* Textbook example strings for testing
        populationStrings[0] = "24748552";
        populationStrings[1] = "32752411";
        populationStrings[2] = "24415124";
        populationStrings[3] = "32543213";
        */
        for (int i = 0; i < numPoplation; i++) {
            populationStrings[i] = "";
            for (int j = 0; j < 8; j++) {
                populationStrings[i] += Random.Range(1,8).ToString();
            }
        }
    }
    public void GetFitness()
    {
        GetScores();
        GetPercentages();
        SortEverything();
        GetProportions();
    }
    //28 is the most clashes possible in any configuration.
    //We want parents with greater fitness to be selected for reproduction.
    //Since that is the cause, we want lower Clash values to be considered
    // of greater fitness, and higher Clash values of lower fitness.
    //To make this happen we start with the worst-case scenario (28)
    // and we subtract from that value the amount of Clahes.
    //A score of 28 is the best.
    public void GetScores()
    {
        populationScores = new int[numPoplation];
        for (int i = 0; i < numPoplation; i++) {
            int myScore = CalculateClashes(populationStrings[i]);
            populationScores[i] = (28-myScore);
        }
    }
    //This creates an array of percentages of based on the elements
    // of each of the strings positions with the string array.
    //This gets the total of all scores, then divides each position,
    // from that total to give it it's own percentage from the rest
    // of the group.
    public void GetPercentages()
    {
        populationPercentages = new float[numPoplation];
        float total = 0;
        for (int i = 0; i < numPoplation; i++) {
            total += populationScores[i];
        }
        for (int i = 0; i < numPoplation; i++) {
            float percent = (float)populationScores[i] / total;
            populationPercentages[i] = percent;
        }
    }
    //The reason this is sorted is that we can then make sure that if
    // no parent is randomly selected, the best one will be selected.
    //It is a very rare circumstance, but does happen about 1/500 times.
    public void SortEverything()
    {
        for (int i = 0; i < numPoplation-1; i++) {
            for (int j = 0; j < numPoplation-i-1; j++) {
                if (populationPercentages[j] > populationPercentages[j+1]) {
                    float tempFloat = populationPercentages[j];
                    populationPercentages[j] = populationPercentages[j+1];
                    populationPercentages[j+1] = tempFloat;
                    int tempInt = populationScores[j];
                    populationScores[j] = populationScores[j+1];
                    populationScores[j+1] = tempInt;
                    string tempString = populationStrings[j];
                    populationStrings[j] = populationStrings[j+1];
                    populationStrings[j+1] = tempString;
                }
            }
        }
    }
    //The percentages are aded up sequentially, one after another.
    //The lower values are stored in the 2d float values at index [n,0]
    // while the upper values are stored in index [n,1]
    //This then creates a range for us to know which parents are
    // selected for reproduction in the SelectParents() function.
    public void GetProportions()
    {
        populationProportions = new float[numPoplation, 2];
        //populationProportions = new float[numPoplation];
        float total = 0;
        for (int i = 0; i < numPoplation; i++) {
            populationProportions[i,0] = total;
            total += populationPercentages[i];
            //populationProportions[i] = total;
            populationProportions[i,1] = total;
            //Debug.Log("\tPopProps["+i+",0] =\t"+populationProportions[i,0]+"\n\t\tPopProps["+i+",1] =\t"+populationProportions[i,1]);
        }
    }
    public void SelectParents()
    {
        selectedParentsStrings = new string[numPoplation];
        for (int i = 0; i < numPoplation; i++) {
            float rollTheDie = Random.Range(0f, 1.0f);
            for (int j = 0; j < numPoplation; j++) {
                float lower = populationProportions[j,0];
                float upper = populationProportions[j,1];
                if (rollTheDie >= lower && rollTheDie <= upper) {
                    selectedParentsStrings[i] = populationStrings[j];
                }
            }
            //Rare event that no parent was selected, this just picks the best
            if (selectedParentsStrings[i] == null) {
                didntMakeAChoice++;
                selectedParentsStrings[i] = populationStrings[numPoplation-1];
            }
        }
    }
    public void CrossOver()
    {
        childrenStrings = new string [numPoplation];
        for (int i = 0; i < numPoplation; i+=2) {
            int division = Random.Range(1, 7);
            string childOne = "";
            string childTwo = "";
            for (int j = 0; j < division; j++) {
                childOne += selectedParentsStrings[i+0].Substring(j, 1);
                childTwo += selectedParentsStrings[i+1].Substring(j, 1);
            }
            /* For testing to see where the division took place
                childOne += '|';
                childTwo += '|';
            */
            for (int j = division; j < 8; j++) {
                childOne += selectedParentsStrings[i+1].Substring(j, 1);
                childTwo += selectedParentsStrings[i+0].Substring(j, 1);
            }
            childrenStrings[i+0] = childOne;
            childrenStrings[i+1] = childTwo;
        }
    }
    // C# didn't make it easy to convert from ints to chars to strings. Yikes.
    /* MUTATECHILDREN()
        decimalPlacement of 0.05 == 100
        number of 0.05 == 5
        Rolls the die for each children in chidren string and rounds the result
            if between 0 and 5
            select a random position
            keep getting a new number until you get a brand new one
            make the swap
    */
    public void MutateChildren()
    {
        int decimalPlacement = (int) Mathf.Pow(10,mutationPct.ToString().Length-2);
        float number = mutationPct*(decimalPlacement);
        for (int i = 0; i < numPoplation; i++) {
            float rollTheDie = Random.Range(0f, decimalPlacement);
            float roundedRoll = Mathf.Round(rollTheDie*1000)/1000;
            //Debug.Log("Chanes are "+number+" in "+decimalPlacement+" and you rolled "+roundedRoll);
            if (roundedRoll <= number) {
                int mutationPos = Random.Range(0,7);
                char[] charArray = childrenStrings[i].ToCharArray();
                char currentCharAtPos = charArray[mutationPos];
                int currentNumAtPos = (int) char.GetNumericValue(currentCharAtPos);
                int updatedNumAtPos = Random.Range(1,8);
                while (updatedNumAtPos == currentNumAtPos) {
                    updatedNumAtPos = Random.Range(1,8);
                }
                string updatedCharAtPos = updatedNumAtPos.ToString();
                //Debug.Log("UpdatedNum = "+updatedNumAtPos+" UpdatedChar = "+updatedCharAtPos);
                string tempChildString = childrenStrings[i];
                childrenStrings[i] = "";
                for (int j = 0; j < 8; j++) {
                    if (j == currentNumAtPos) {
                        childrenStrings[i] += updatedCharAtPos.Substring(0,1);
                    } else {
                        childrenStrings[i] += tempChildString.Substring(j,1);
                    }
                }
                //Debug.Log("Mutated: "+tempChildString+" to "+childrenStrings[i]);
            }
        }
    }
    public void MakeNewGeneration()
    {
        populationStrings = new string[numPoplation];
        for (int i = 0; i < numPoplation; i++) {
            populationStrings[i] = childrenStrings[i];
        }
    }
    public void DisableButtons()
    {
        GoButton.interactable = false;
        initPopInput.interactable = false;
        numIterationInput.interactable = false;
        mutationPctInput.interactable = false;
    }
    public void GetTheBest()
    {
        for (int i = 0; i < numPoplation; i++) {
            if (populationScores[i] > theHighestScore) {
                theHighestScore = populationScores[i];
                theHighestString = populationStrings[i];
                //Debug.Log(theHighestString+" with "+(CalculateClashes(theHighestString)).ToString()+" clashes!");
            }
        }
    }
    public void UpdateChart()
    {
        float averageScore = AverageScore();
        //Debug.Log("AVERAGE SCORE IS "+averageScore);
        theChartScript.UpdateValues(averageScore, (float) currentIteration);
    }
    public float AverageScore()
    {
        float total = 0;
        for (int i = 0; i < numPoplation; i++) {
            total += populationScores[i];
        }
        float averageScore = total / numPoplation;
        return Mathf.Round(averageScore*1000) / 1000;
    }
}
