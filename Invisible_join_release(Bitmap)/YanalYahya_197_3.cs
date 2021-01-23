using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace Yanal_Yahya_197_HW4
{
    /// <summary>
    /// abstract Bitmap class  
    /// </summary>
    public abstract class Bitmap
    {
        public abstract void And(Bitmap other);
        public abstract void Set(int i, bool value);
        public abstract bool Get(int i);

    }

    /// <summary>
    /// inherited class from Bitmap class
    /// </summary>
    class MyBitmap : Bitmap
    {
        static readonly ushort maxUShort = ushort.MaxValue;
        //array in which data will be saved in arrayContainer or bitmapContainer
        MyBitmap[] ArrayOfContainers;
        ushort cardinality = 0;
        ushort[] arrayContainer = new ushort[0];
        uint[] bitmapContainer = new uint[0];

        /// <summary>
        /// intersection of two ArrayOfContainers
        /// </summary>
        /// <param name="other"> second ArrayOfContainers </param>
        public override void And(Bitmap other)
        {

            MyBitmap myOther;
            try
            {
                myOther = other as MyBitmap;
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }

            for (int i = 0; i < ArrayOfContainers.Length; i++)
            {
                if (myOther.ArrayOfContainers == null || ArrayOfContainers == null)
                {
                    throw new NullReferenceException("Not Right test");
                }
                //if both containers is array
                if (ArrayOfContainers[i].arrayContainer != null &&
                    myOther.ArrayOfContainers[i].arrayContainer != null)
                    And_Array_Array(myOther, i);
                //if first container is array and the second is bitmap
                else if (ArrayOfContainers[i].arrayContainer != null &&
                    myOther.ArrayOfContainers[i].arrayContainer == null)
                    And_Array_Bitmap(myOther, i);
                //if both containers are bitmaps
                else
                    And_bitmap_bitmap(myOther, i);
            }

        }

        /// <summary>
        /// method to calculate intersection of two array containers
        /// </summary>
        /// <param name="myOther"> we need its array container </param>
        /// <param name="i">ArrayOfContainers index </param>
        private void And_Array_Array(MyBitmap myOther, int i)
        {
            ArrayOfContainers[i].arrayContainer = ArrayOfContainers[i].arrayContainer.
                Intersect(myOther.ArrayOfContainers[i].arrayContainer).ToArray();
            ArrayOfContainers[i].cardinality = (ushort)ArrayOfContainers[i].arrayContainer.Length;
        }

        /// <summary>
        /// method to calculate intersection of two bitmap containers
        /// </summary>
        /// <param name="myOther"> we need its bitmap container </param>
        /// <param name="i">ArrayOfContainers index </param>
        private void And_bitmap_bitmap(MyBitmap myOther, int i)
        {

            int minLength = (myOther.ArrayOfContainers[i].bitmapContainer.Length <
                ArrayOfContainers[i].bitmapContainer.Length) ?
                myOther.ArrayOfContainers[i].bitmapContainer.Length :
                ArrayOfContainers[i].bitmapContainer.Length;
            uint[] bitmapContainerResult = new uint[minLength];
            for (int j = 0; j < minLength; j++)
            {
                bitmapContainerResult[j] = (myOther.ArrayOfContainers[i].bitmapContainer[j]
                    & ArrayOfContainers[i].bitmapContainer[j]);
            }
            ArrayOfContainers[i].bitmapContainer = bitmapContainerResult;
            ArrayOfContainers[i].cardinality = GetCardinality(ArrayOfContainers[i].bitmapContainer);
            if (ArrayOfContainers[i].cardinality <= 4096)
            {
                ArrayOfContainers[i].TransferBitmapContainerToArrayContainer();
            }

        }

        /// <summary>
        /// method to calculate intersection of array container with bitmap container
        /// </summary>
        /// <param name="myOther"> we need its bitmap container </param>
        /// <param name="i">ArrayOfContainers index </param>
        private void And_Array_Bitmap(MyBitmap myOther, int i)
        {
            int arrayContainerLenght = ArrayOfContainers[i].arrayContainer.Length;
            int index = 0;
            while (arrayContainerLenght > 0)
            {
                if (!myOther.Get(ArrayOfContainers[i].arrayContainer[index]))
                {
                    ArrayOfContainers[i].RemoveAt(ref ArrayOfContainers[i].arrayContainer, index);
                    --arrayContainerLenght;
                    continue;
                }
                --arrayContainerLenght;
                ++index;
            }
            ArrayOfContainers[i].cardinality = (ushort)ArrayOfContainers[i].arrayContainer.Length;
        }

        /// <summary>
        /// method for calculating the cordinality of bitmap container
        /// </summary>
        /// <param name="bitmapContainer"> the bitmap containwe</param>
        /// <returns>cordinality of bitmap container</returns>
        private ushort GetCardinality(uint[] bitmapContainer)
        {
            ushort count = 0;
            foreach (var item in bitmapContainer)
            {
                for (int i = 0; i < 32; i++)
                {
                    if (((1u << i) & item) > 0)
                        ++count;
                }
            }
            return count;
        }

        /// <summary>
        /// check if element is existing in ArrayOfContainers
        /// </summary>
        /// <param name="i"> the element</param>
        /// <returns></returns>
        public override bool Get(int i)
        {
            return ContainInBitmap(i);

        }

        /// <summary>
        /// method for setting or removing an element into or from suitable container type
        /// </summary>
        /// <param name="i"> the element</param>
        /// <param name="value">true to add element, false to remove element</param>
        public override void Set(int i, bool value)
        {
            int indexCon = (int)(i / (maxUShort + 1));
            PrepareArrayOfContainers(indexCon);
            bool contain = ContainInBitmap(i);
            if (value)
                SetIntElement(indexCon, i, contain);
            else if (!value && contain)
                RemoveIntElement(indexCon, i);
        }

        /// <summary>
        /// method for setting element into suitable container
        /// </summary>
        /// <param name="indexCon"> index of main container</param>
        /// <param name="i"> the element</param>
        /// <param name="contain"> true if the element already exist in some container
        /// , false otherwise</param>
        private void SetIntElement(int indexCon, int i, bool contain)
        {
            if (ArrayOfContainers[indexCon].cardinality <= 4096)
            {
                if (!contain)
                    AddElementToSortedArrayContainer(ref ArrayOfContainers[indexCon].arrayContainer, i);

                if (ArrayOfContainers[indexCon].arrayContainer.Length > 4096)
                    ArrayOfContainers[indexCon].TransferArrayContainerToBitmapContainer();
                ++ArrayOfContainers[indexCon].cardinality;
            }
            else
            {
                if (contain)
                    return;
                else
                {
                    int bitPosition = i % (maxUShort + 1);
                    int bitmapContainerIndex = bitPosition / 32;
                    if (bitmapContainerIndex >= ArrayOfContainers[indexCon].bitmapContainer.Length)
                        Array.Resize(ref ArrayOfContainers[indexCon].bitmapContainer,
                            bitmapContainerIndex + 1);
                    ArrayOfContainers[indexCon].bitmapContainer[bitmapContainerIndex] |=
                        1u << (bitPosition % 32);
                    ++ArrayOfContainers[indexCon].cardinality;
                }
            }
        }

        /// <summary>
        /// method for removing an element from specific container
        /// </summary>
        /// <param name="indexCon"> index of main container </param>
        /// <param name="i"> the element </param>
        private void RemoveIntElement(int indexCon, int i)
        {
            if (ArrayOfContainers[indexCon].cardinality <= 4096)
            {
                RemoveAt(ref ArrayOfContainers[indexCon].arrayContainer,
                    Array.BinarySearch(arrayContainer, i));
                --ArrayOfContainers[indexCon].cardinality;
            }
            else
            {
                int bitPosition = i % (maxUShort + 1);
                int bitmapContainerIndex = bitPosition / 32;
                if (bitmapContainerIndex >= ArrayOfContainers[indexCon].bitmapContainer.Length)
                    Array.Resize(ref ArrayOfContainers[indexCon].bitmapContainer,
                        bitmapContainerIndex + 1);
                ArrayOfContainers[indexCon].bitmapContainer[bitmapContainerIndex] ^=
                    1u << (bitPosition % 32);
                --ArrayOfContainers[indexCon].cardinality;
                if (cardinality <= 4096)
                    ArrayOfContainers[indexCon].TransferBitmapContainerToArrayContainer();
            }
        }

        /// <summary>
        /// method to prepare the ArrayOfContainers container ( initialize or resize it )
        /// </summary>
        /// <param name="indexCon"> index of ArrayOfContainers container</param>
        private void PrepareArrayOfContainers(int indexCon)
        {
            if (ArrayOfContainers == null)
            {
                ArrayOfContainers = new MyBitmap[1];
                ArrayOfContainers[0] = new MyBitmap();
            }
            if (ArrayOfContainers.Length <= indexCon)
            {
                Array.Resize(ref ArrayOfContainers, indexCon + 1);
                ArrayOfContainers[indexCon] = new MyBitmap();
            }
        }

        /// <summary>
        /// method for transfering the bitmap container to array container
        /// </summary>
        private void TransferBitmapContainerToArrayContainer()
        {
            int index = 0;
            foreach (uint item in bitmapContainer)
            {

                for (int i = 0; i < 32; i++)
                {
                    if (((1u << i) & item) > 0)
                        AddElementToSortedArrayContainer(ref arrayContainer, index * 32 + i);
                }
                ++index;
            }
            bitmapContainer = new uint[0];
        }
        /// <summary>
        /// method for transfering the array container to bitmap container
        /// </summary>
        private void TransferArrayContainerToBitmapContainer()
        {
            foreach (ushort item in arrayContainer)
            {
                int bitPosition = item % (maxUShort + 1);
                int bitmapContainerIndex = bitPosition / 32;
                if (bitmapContainerIndex >= bitmapContainer.Length)
                    Array.Resize(ref bitmapContainer, bitmapContainerIndex + 1);
                bitmapContainer[bitmapContainerIndex] |= 1u << (bitPosition % 32);
            }
            arrayContainer = null;
        }

        /// <summary>
        /// removing element from array container
        /// </summary>
        /// <param name="arrayContainer"> from where will be element removed </param>
        /// <param name="index"> element's index in arrayContainer</param>
        private void RemoveAt(ref ushort[] arrayContainer, int index)
        {
            for (int i = index; i < arrayContainer.Length - 1; i++)
            {
                // moving elements downwards, to fill the gap at [index]
                arrayContainer[i] = arrayContainer[i + 1];
            }
            // finally, let's decrement Array's size by one
            Array.Resize(ref arrayContainer, arrayContainer.Length - 1);
        }

        /// <summary>
        /// method for setting element into sorted array container, and keep it sorted
        /// </summary>
        /// <param name="array"> array container where element will be sorted</param>
        /// <param name="i"> the element which will be set into array container </param>
        public void AddElementToSortedArrayContainer(ref ushort[] array, int i)
        {
            if (array == null)
                array = new ushort[0];
            ushort[] resultArray = new ushort[array.Length + 1];
            var index = 0;
            while (index < array.Length && array[index] < i)
            {
                resultArray[index] = array[index];
                ++index;
            }
            resultArray[index++] = (ushort)i;
            while (index < resultArray.Length)
            {
                resultArray[index] = array[index - 1];
                ++index;
            }
            array = resultArray;
        }

        /// <summary>
        /// method for checking about specific element in array container or bitmap container
        /// </summary>
        /// <param name="x"> the element </param>
        /// <returns> is element exist? (true, false)</returns>
        private bool ContainInBitmap(int x)
        {
            int indexCon = (int)(x / (maxUShort + 1));
            if (ArrayOfContainers != null && ArrayOfContainers.Length > indexCon &&
                ArrayOfContainers[indexCon] != null)
            {
                if (ArrayOfContainers[indexCon].cardinality <= 4096)
                {
                    if (ArrayOfContainers[indexCon].arrayContainer == null || ArrayOfContainers[indexCon].arrayContainer.Length == 0)
                        return false;
                    return !(Array.BinarySearch(ArrayOfContainers[indexCon].arrayContainer,
                        (ushort)x) < 0);
                }
                else
                {

                    int bitPosition = x % (maxUShort + 1);
                    int bitmapContainerIndex = bitPosition / 32;
                    if (ArrayOfContainers[indexCon].bitmapContainer.Length <= bitmapContainerIndex)
                        return false;
                    return ((ArrayOfContainers[indexCon].bitmapContainer[bitmapContainerIndex]) &
                        1u << (bitPosition % 32)) != 0;
                }

            }
            else
                return false;
        }
    }

    class YanalYahya_197_3
    {
        /// <summary>
        /// here is a dictionary clarifies setting of dim files 
        /// </summary>
        static readonly Dictionary<string, Dictionary<string, int>> allDimFilesAndTheirColumnsIndex =
            new Dictionary<string, Dictionary<string, int>>
            {
                ["DimProduct"] = new Dictionary<string, int>
                {
                    ["ProductKey"] = 0,
                    ["ProductAlternateKey"] = 1,
                    ["EnglishProductName"] = 2,
                    ["Color"] = 3,
                    ["SafetyStockLevel"] = 4,
                    ["ReorderPoint"] = 5,
                    ["SizeRange"] = 6,
                    ["DaysToManufacture"] = 7,
                    ["StartDate"] = 8
                },
                ["DimReseller"] = new Dictionary<string, int>
                {
                    ["ResellerKey"] = 0,
                    ["ResellerAlternateKey"] = 1,
                    ["Phone"] = 2,
                    ["BusinessType"] = 3,
                    ["ResellerName"] = 4,
                    ["NumberEmployees"] = 5,
                    ["OrderFrequency"] = 6,
                    ["ProductLine"] = 7,
                    ["AddressLine1"] = 8,
                    ["BankName"] = 9,
                    ["YearOpened"] = 10
                },
                ["DimCurrency"] = new Dictionary<string, int>
                {
                    ["CurrencyKey"] = 0,
                    ["CurrencyAlternateKey"] = 1,
                    ["CurrencyName"] = 2
                },
                ["DimPromotion"] = new Dictionary<string, int>
                {
                    ["PromotionKey"] = 0,
                    ["PromotionAlternateKey"] = 1,
                    ["EnglishPromotionName"] = 2,
                    ["EnglishPromotionType"] = 3,
                    ["EnglishPromotionCategory"] = 4,
                    ["StartDate"] = 5,
                    ["EndDate"] = 6,
                    ["MinQty"] = 7
                },
                ["DimSalesTerritory"] = new Dictionary<string, int>
                {
                    ["SalesTerritoryKey"] = 0,
                    ["SalesTerritoryAlternateKey"] = 1,
                    ["SalesTerritoryRegion"] = 2,
                    ["SalesTerritoryCountry"] = 3,
                    ["SalesTerritoryGroup"] = 4
                },
                ["DimEmployee"] = new Dictionary<string, int>
                {
                    ["EmployeeKey"] = 0,
                    ["FirstName"] = 1,
                    ["LastName"] = 2,
                    ["Title"] = 3,
                    ["BirthDate"] = 4,
                    ["LoginID"] = 5,
                    ["EmailAddress"] = 6,
                    ["Phone"] = 7,
                    ["MaritalStatus"] = 8,
                    ["Gender"] = 9,
                    ["PayFrequency"] = 10,
                    ["VacationHours"] = 11,
                    ["SickLeaveHours"] = 12,
                    ["DepartmentName"] = 13,
                    ["StartDate"] = 14
                },
                ["DimDate"] = new Dictionary<string, int>
                {
                    ["DateKey"] = 0,
                    ["FullDateAlternateKey"] = 1,
                    ["DayNumberOfWeek"] = 2,
                    ["EnglishDayNameOfWeek"] = 3,
                    ["DayNumberOfMonth"] = 4,
                    ["DayNumberOfYear"] = 5,
                    ["WeekNumberOfYear"] = 6,
                    ["EnglishMonthName"] = 7,
                    ["MonthNumberOfYear"] = 8,
                    ["CalendarQuarter"] = 9,
                    ["CalendarYear"] = 10,
                    ["CalendarSemester"] = 11,
                    ["FiscalQuarter"] = 12,
                    ["FiscalYear"] = 13,
                    ["FiscalSemester"] = 14
                }
            };

        /// <summary>
        /// saving the first line in input file in array where will be saved 
        /// list of fields in the output table
        /// </summary>
        static string[] firstLine;
        /// <summary>
        /// number of condtions in input file
        /// </summary>
        static int conditionNum;
        /// <summary>
        /// array for saving the list of conditions in input file
        /// </summary>
        static string[] conditionsArray;
        static string arg1, arg2, arg3;
        //main function
        static void Main(string[] args)
        {
            // try
            // {
            arg1 = args[0];
            arg2 = args[1];
            arg3 = args[2];
            //reading data into fields from test file
            ReadTestFile();
            Bitmap[] bitmapsOfKeysFromFiltrationFase_1 = new MyBitmap[conditionNum];
            Bitmap[] bitmapsOfFase_2_Step_1 = new MyBitmap[conditionNum];
            for (int j = 0; j < conditionsArray.Length; j++)
            {
                string[] subline = conditionsArray[j].Split(' ');
                for (int i = 3; i < subline.Length; i++)
                    subline[2] += " " + subline[i];
                if (subline[2][0] == '\'')
                    subline[2] = subline[2].Substring(1, subline[2].Length - 2);
                bitmapsOfKeysFromFiltrationFase_1[j] = GreatBitmapUsingConditionFase_1(subline);
                bitmapsOfFase_2_Step_1[j] = GetBitmapInFase2_Step_1(bitmapsOfKeysFromFiltrationFase_1[j],
                    subline);
            }
            Bitmap resultOfFase_2 = null;
            if (conditionNum > 0)
            {
                //Do "And" operation to the bitmaps in fase 2
                resultOfFase_2 = GetResultOfIntersectionFase_2_Step_2(bitmapsOfFase_2_Step_1);
            }
            MovtingToFase_3(resultOfFase_2);
            //  }
            // catch (NullReferenceException)
            // {
            //     using (StreamWriter writer = new StreamWriter(new FileStream(arg3, FileMode.Create, FileAccess.Write))) { }
            // }
            //catch (Exception ex)
            //{
            //    Console.WriteLine(ex.Message + "\n" + ex.TargetSite);
            //}

        }

        /// <summary>
        /// method for managementing the fase 3 step 
        /// </summary>
        /// <param name="resultOfFase_2"></param>
        private static void MovtingToFase_3(Bitmap resultOfFase_2)
        {
            string[] dimFilesName = Array.FindAll(firstLine, x => x.Split('.')[0] != "FactResellerSales");
            Bitmap[] bitmaps = FirstStepOfInvisibleJoinFase_3(resultOfFase_2, dimFilesName);
            Dictionary<int, string>[] dicOfNeededValuesFromDimFiles = dimFilesName.Length != 0 ?
                     GetDicOfNeededValuesFromDimFiles(dimFilesName, bitmaps) : new Dictionary<int, string>[0];

            GetFactTableInter(resultOfFase_2, dicOfNeededValuesFromDimFiles);
        }

        /// <summary>
        /// method for getting array of bitmaps which contains specific foreign keys from fact table
        /// of needed dim files using the result bitmap of fase 2 (result of "and operation") 
        /// </summary>
        /// <param name="resultOfFase_2"> result bitmap of fase 2 (result of "and operation") </param>
        /// <param name="dimFilesName">list of fields(in dim files) in the output table</param>
        /// <returns></returns>
        private static Bitmap[] FirstStepOfInvisibleJoinFase_3(Bitmap resultOfFase_2, string[] dimFilesName)
        {

            StreamReader[] streamReaders = new StreamReader[dimFilesName.Length];
            Bitmap[] bitmaps = new MyBitmap[dimFilesName.Length];
            string[] saveReaders = new string[dimFilesName.Length];
            //opening required files (it's a foreign key columns in fact table)
            for (int i = 0; i < dimFilesName.Length; i++)
            {
                bitmaps[i] = new MyBitmap();
                string[] fileNameAndColumn = dimFilesName[i].Split('.');
                streamReaders[i] = new StreamReader(new FileStream(arg1 + "/FactResellerSales." +
                fileNameAndColumn[0].Replace("Dim", (fileNameAndColumn[0] == "DimDate" ? "Order" : "")) +
                "Key.csv", FileMode.Open, FileAccess.Read));

            }
            int index = 1;
            while (streamReaders.Length != 0 && (saveReaders[0] = streamReaders[0].ReadLine()) != null
                && saveReaders[0] != "")
            {
                for (int i = 1; i < saveReaders.Length; i++)
                    saveReaders[i] = streamReaders[i].ReadLine();//reading first line from all open files
                if (resultOfFase_2 == null)
                {
                    for (int i = 0; i < bitmaps.Length; i++)
                    {
                        int valueToSave = int.Parse(saveReaders[i]);
                        if (!bitmaps[i].Get(valueToSave))
                            bitmaps[i].Set(valueToSave, true);//set foreign key in bitmap
                    }
                }
                else if (resultOfFase_2.Get(index))
                {
                    for (int i = 0; i < bitmaps.Length; i++)
                    {
                        int valueToSave = int.Parse(saveReaders[i]);
                        if (!bitmaps[i].Get(valueToSave))
                            bitmaps[i].Set(valueToSave, true);//set foreign key in bitmap
                    }
                }
                ++index;
            }
            //closing open files
            for (int i = 0; i < streamReaders.Length; i++)
                streamReaders[i].Dispose();
            return bitmaps;
        }

        /// <summary>
        /// method for getting an array of dictionaries, in which will be saved premary key 
        /// as dictionary's key and the needed coulumn value as dic's value,
        /// and we should take those premary keys which was token befor from fact table as foreign keys
        /// </summary>
        /// <param name="dimFilesName"> dim files from where we should get our output </param>
        /// <param name="bitmaps"> result of FirstStepOfInvisibleJoinFase_3 function</param>
        /// <returns></returns>
        private static Dictionary<int, string>[] GetDicOfNeededValuesFromDimFiles(string[] dimFilesName,
            Bitmap[] bitmaps)
        {
            Dictionary<int, string>[] dicOfNeededValuesFromDimFiles = new Dictionary<int, string>[dimFilesName.Length];
            StreamReader[] streamReaders = new StreamReader[dimFilesName.Length];
            string line;
            for (int i = 0; i < dimFilesName.Length; i++)
            {
                dicOfNeededValuesFromDimFiles[i] = new Dictionary<int, string>();
                string[] fileNameAndColumn = dimFilesName[i].Split('.');
                streamReaders[i] = new StreamReader(new FileStream(arg1 + "/" +
                    fileNameAndColumn[0] + ".csv", FileMode.Open, FileAccess.Read));
                while ((line = streamReaders[i].ReadLine()) != null && line != "")
                {
                    string[] columnsValues = line.Split('|');
                    int key = int.Parse(columnsValues[0]);
                    if (bitmaps[i].Get(key))
                        dicOfNeededValuesFromDimFiles[i].Add(key, columnsValues
                            [allDimFilesAndTheirColumnsIndex[fileNameAndColumn[0]][fileNameAndColumn[1]]]);
                }
                streamReaders[i].Dispose();
            }
            return dicOfNeededValuesFromDimFiles;

        }

        /// <summary>
        /// method of invisible join(fase 3), here will be the process of printing 
        /// output result into result file
        /// </summary>
        /// <param name="resultOfFase_2"> the result of "And" operation in fase 2</param>
        /// <param name="dicOfNeededValuesFromDimFiles"> result of
        /// GetDicOfNeededValuesFromDimFiles function</param>
        private static void GetFactTableInter(Bitmap resultOfFase_2,
            Dictionary<int, string>[] dicOfNeededValuesFromDimFiles)
        {

            string[] dimFilesName = Array.FindAll(firstLine, x => x.Split('.')[0] != "FactResellerSales");
            StreamReader[] Readers = new StreamReader[dimFilesName.Length];
            string[] saveReaders = new string[dimFilesName.Length];
            //opening fact table files (foreign columns of FactResellerSales file)
            for (int i = 0; i < dimFilesName.Length; i++)
            {
                string[] fileNameAndColumn = dimFilesName[i].Split('.');
                Readers[i] = new StreamReader(new FileStream(arg1 + "/FactResellerSales." +
                fileNameAndColumn[0].Replace("Dim", (fileNameAndColumn[0] == "DimDate" ? "Order" : "")) +
                "Key.csv", FileMode.Open, FileAccess.Read));
            }

            string[] dimFilesName2 = Array.FindAll(firstLine, x => x.Split('.')[0] == "FactResellerSales");
            StreamReader[] streamReaders = new StreamReader[dimFilesName2.Length];
            string[] saveStreamReaders = new string[dimFilesName2.Length];
            //opening fact table files (not foreign columns of FactResellerSales file)
            for (int i = 0; i < dimFilesName2.Length; i++)
                streamReaders[i] = new StreamReader(new FileStream(arg1 + "/" +
                    dimFilesName2[i] + ".csv", FileMode.Open, FileAccess.Read));

            int premaryKeyInFactTable = 1;
            using (StreamWriter writer = new StreamWriter(new FileStream(arg3,
                FileMode.Create, FileAccess.Write)))
            {
                while ((streamReaders.Length != 0 &&
                    (saveStreamReaders[0] = streamReaders[0].ReadLine()) != null &&
                     saveStreamReaders[0] != "") || (Readers.Length != 0 &&
                     (saveReaders[0] = Readers[0].ReadLine()) != null && saveReaders[0] != ""))
                {
                    /*
                     * reading first line from all open files
                     */
                    for (int i = 1; i < saveStreamReaders.Length; i++)
                        saveStreamReaders[i] = streamReaders[i].ReadLine();
                    for (int i = (streamReaders.Length == 0 ? 1 : 0); i < Readers.Length; i++)
                        saveReaders[i] = Readers[i].ReadLine();
                    if (resultOfFase_2 == null)
                    {
                        int ind1 = 0, ind2 = 0;
                        for (int i = 0; i < firstLine.Length; i++)
                        {
                            if (firstLine[i].Contains("FactResellerSales"))
                            {
                                //value from fact table
                                writer.Write(saveStreamReaders[ind1] +
                                    (i == firstLine.Length - 1 ? "" : "|"));
                                ind1++;
                            }
                            else
                            {
                                //value from dim table, we use our dictionary to get it
                                writer.Write(dicOfNeededValuesFromDimFiles[ind2]
                                    [int.Parse(saveReaders[ind2])] +
                                    (i == firstLine.Length - 1 ? "" : "|"));
                                ind2++;
                            }

                        }
                        writer.WriteLine();
                    }
                    else if (resultOfFase_2.Get(premaryKeyInFactTable))
                    {

                        int ind1 = 0, ind2 = 0;
                        for (int i = 0; i < firstLine.Length; i++)
                        {
                            if (firstLine[i].Contains("FactResellerSales"))
                            {
                                //value from fact table
                                writer.Write(saveStreamReaders[ind1] +
                                    (i == firstLine.Length - 1 ? "" : "|"));
                                ind1++;
                            }
                            else
                            {
                                //value from dim table, we use our dictionary to get it
                                writer.Write(dicOfNeededValuesFromDimFiles[ind2]
                                    [int.Parse(saveReaders[ind2])] +
                                    (i == firstLine.Length - 1 ? "" : "|"));
                                ind2++;
                            }

                        }
                        writer.WriteLine();
                    }
                    ++premaryKeyInFactTable;
                }
            }
            for (int i = 0; i < streamReaders.Length; i++)
                streamReaders[i].Dispose();
            for (int i = 0; i < Readers.Length; i++)
                Readers[i].Dispose();
        }

        /// <summary>
        /// method for calculating the result of "And" operation between bitmaps in some array
        /// </summary>
        /// <param name="bitmapsOfFase_2"> array of bitmaps</param>
        /// <returns> bitmap contain the result of and operation between group of bitmaps</returns>
        private static MyBitmap GetResultOfIntersectionFase_2_Step_2(Bitmap[] bitmapsOfFase_2)
        {
            for (int i = 1; i < bitmapsOfFase_2.Length; i++)
            {
                bitmapsOfFase_2[0].And(bitmapsOfFase_2[i]);
            }
            return (MyBitmap)bitmapsOfFase_2[0];
        }

        /// <summary>
        /// method for setting containing keyes in a bitmap
        /// </summary>
        /// <param name="filterBitmap"> contains value of the keys from 
        /// dim or fact table of the lines where conditions was met</param>
        /// <param name="subline"> contain a line from conditions list</param>
        /// <returns> a bitmap contains the keys of fact table, where external key 
        /// of specific dimension file existing in filter Bitmap </returns>
        private static Bitmap GetBitmapInFase2_Step_1(Bitmap filterBitmap, string[] subline)
        {
            string[] filePathAndCol = subline[0].Split('.');
            /*
             * if the first condtion operand in FactResellerSales 
             * table so the result is the same as in the first fase
             */
            if (filePathAndCol[0] == "FactResellerSales")
            {
                return filterBitmap;
            }
            Bitmap result = new MyBitmap();
            string line;
            //opening dimension file
            using (FileStream file = new FileStream(arg1 + "/FactResellerSales." +
                (filePathAndCol[0] == "DimDate" ? "OrderDateKey" :
                allDimFilesAndTheirColumnsIndex[filePathAndCol[0]].First().Key) + ".csv",
                FileMode.Open, FileAccess.Read))
            using (StreamReader reader = new StreamReader(file))
            {
                int index = 1;
                while ((line = reader.ReadLine()) != null && line != "")
                {
                    int keyValue = int.Parse(line);
                    if (filterBitmap.Get(keyValue))
                        result.Set(index, true);
                    ++index;
                }
            }
            return result;
        }

        /// <summary>
        /// method for creating a bitmaps of fase 1, which contain a
        /// primary keys of specific files, where conditions will be met
        /// </summary>
        /// <param name="subline"> line of condtions list</param>
        /// <returns></returns>
        private static MyBitmap GreatBitmapUsingConditionFase_1(string[] subline)
        {
            string[] filePathAndCol = subline[0].Split('.');
            if (filePathAndCol[0] == "FactResellerSales")
                return GetBitmapFrom_FactTable_UsingConditionFase_1(subline);
            else
                return GetBitmapFrom_DimFile_UsingConditionFase_1(subline, filePathAndCol);

        }

        /// <summary>
        /// method for building a bitmaps which contains primary keys of lines 
        /// where reciveed condtion is right
        /// </summary>
        /// <param name="subline">some line from condtions list where intended file 
        /// is "FactResellerSales" </param>
        /// <returns>bitmap contains primary keys of lines 
        /// where reciveed condtion is right </returns>
        private static MyBitmap GetBitmapFrom_FactTable_UsingConditionFase_1(string[] subline)
        {
            MyBitmap bitmap = new MyBitmap();
            string line;
            int index = 1;
            using (FileStream file = new FileStream(arg1 + "/" + subline[0] + ".csv",
                FileMode.Open, FileAccess.Read))
            using (StreamReader reader = new StreamReader(file))
            {
                //case of operation
                switch (subline[1])
                {
                    case "=":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            if (line == subline[2])
                                bitmap.Set(index, true);
                            ++index;
                        }
                        break;
                    case ">":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            if (CheckBiggest(line, subline[2]))
                                bitmap.Set(index, true);
                            ++index;
                        }
                        break;
                    case "<":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            if (CheckSmallest(line, subline[2]))
                                bitmap.Set(index, true);
                            ++index;
                        }
                        break;
                    case "<=":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            if (CheckSmallestOrEqualization(line, subline[2]))
                                bitmap.Set(index, true);
                            ++index;
                        }
                        break;
                    case ">=":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            if (CheckBiggestOrEqualization(line, subline[2]))
                                bitmap.Set(index, true);
                            ++index;
                        }
                        break;
                    case "<>":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            if (line != subline[2])
                                bitmap.Set(index, true);
                            ++index;
                        }
                        break;
                    default:
                        break;
                }
            }
            return bitmap;
        }

        /// <summary>
        /// method for building a bitmaps which contains primary keys of lines
        /// where reciveed condtion is right
        /// </summary>
        /// <param name="subline"> some line from condtions list where intended file 
        /// is some dimension file </param>
        /// <param name="filePathAndCol"> name of dimension file with the name of
        /// intended column </param>
        /// <returns> bitmap contains primary keys of lines 
        /// where reciveed condtion is right</returns>
        private static MyBitmap GetBitmapFrom_DimFile_UsingConditionFase_1(string[] subline,
            string[] filePathAndCol)
        {
            string[] columnValues;
            string line;
            MyBitmap bitmap = new MyBitmap();
            using (FileStream file = new FileStream(arg1 + "/" + filePathAndCol[0] + ".csv",
                FileMode.Open, FileAccess.Read))
            using (StreamReader reader = new StreamReader(file))
            {
                switch (subline[1])
                {
                    case "=":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            columnValues = line.Split('|');
                            /*
                             *  finding the index of column in table using the dictionary, which 
                             *  was initialized at the first of this file, and then get suitable value from table
                             */
                            string valueForChecking =
                                columnValues[allDimFilesAndTheirColumnsIndex[filePathAndCol[0]][filePathAndCol[1]]];
                            if (valueForChecking == subline[2])
                                bitmap.Set(int.Parse(columnValues[0]), true);
                        }

                        break;
                    case ">":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            columnValues = line.Split('|');
                            string valueForChecking =
                                columnValues[allDimFilesAndTheirColumnsIndex[filePathAndCol[0]][filePathAndCol[1]]];
                            if (CheckBiggest(valueForChecking, subline[2]))
                                bitmap.Set(int.Parse(columnValues[0]), true);
                        }

                        break;
                    case "<":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            columnValues = line.Split('|');
                            string valueForChecking =
                                columnValues[allDimFilesAndTheirColumnsIndex[filePathAndCol[0]][filePathAndCol[1]]];
                            if (CheckSmallest(valueForChecking, subline[2]))
                                bitmap.Set(int.Parse(columnValues[0]), true);
                        }

                        break;
                    case "<=":

                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            columnValues = line.Split('|');
                            string valueForChecking =
                                columnValues[allDimFilesAndTheirColumnsIndex[filePathAndCol[0]][filePathAndCol[1]]];
                            if (CheckSmallestOrEqualization(valueForChecking, subline[2]))
                                bitmap.Set(int.Parse(columnValues[0]), true);
                        }

                        break;
                    case ">=":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            columnValues = line.Split('|');
                            string valueForChecking =
                                columnValues[allDimFilesAndTheirColumnsIndex[filePathAndCol[0]][filePathAndCol[1]]];
                            if (CheckBiggestOrEqualization(valueForChecking, subline[2]))
                                bitmap.Set(int.Parse(columnValues[0]), true);
                        }
                        break;
                    case "<>":
                        while ((line = reader.ReadLine()) != null && line != "")
                        {
                            columnValues = line.Split('|');
                            string valueForChecking =
                                columnValues[allDimFilesAndTheirColumnsIndex[filePathAndCol[0]][filePathAndCol[1]]];
                            if (valueForChecking != subline[2])
                                bitmap.Set(int.Parse(columnValues[0]), true);
                        }
                        break;
                    default:
                        break;
                }
            }
            return bitmap;
        }

        /// <summary>
        /// method for checking the biggest value of two values or their equalization
        /// which can have a types: short - int - byte - string
        /// </summary>
        /// <param name="valueForChecking"> frist operand</param>
        /// <param name="neededValue"> second operand</param>
        /// <returns> if the first operand bigger or equal the second</returns>
        private static bool CheckBiggestOrEqualization(string valueForChecking, string neededValue)
        {
            int operand1;
            if (int.TryParse(neededValue, out int operand2))
            {
                operand1 = int.Parse(valueForChecking);
                if (operand1 >= operand2)
                    return true;
                return false;
            }
            else if (valueForChecking.CompareTo(neededValue) >= 0)
                return true;
            return false;
        }

        /// <summary>
        /// method for checking the smallest value of two values or their equalization
        /// which can have a types: short - int - byte - string
        /// </summary>
        /// <param name="valueForChecking"> frist operand</param>
        /// <param name="neededValue"> second operand</param>
        /// <returns> if the first operand smaller or equal the second</returns>
        private static bool CheckSmallestOrEqualization(string valueForChecking, string neededValue)
        {
            int operand1;
            if (int.TryParse(neededValue, out int operand2))
            {
                operand1 = int.Parse(valueForChecking);
                if (operand1 <= operand2)
                    return true;
            }
            else if (valueForChecking.CompareTo(neededValue) <= 0)
                return true;
            return false;
        }

        /// <summary>
        /// method for checking the smallest value of two values 
        /// which can have a types: short - int - byte - string
        /// </summary>
        /// <param name="valueForChecking"> frist operand</param>
        /// <param name="neededValue"> second operand</param>
        /// <returns> if the first operand smaller than the second</returns>
        private static bool CheckSmallest(string valueForChecking, string neededValue)
        {
            int operand1;
            if (int.TryParse(neededValue, out int operand2))
            {
                operand1 = int.Parse(valueForChecking);
                if (operand1 < operand2)
                    return true;
            }
            else if (valueForChecking.CompareTo(neededValue) == -1)
                return true;
            return false;
        }

        /// <summary>
        /// method for checking the biggest value of two values 
        /// which can have a types: short - int - byte - string
        /// </summary>
        /// <param name="valueForChecking"> frist operand</param>
        /// <param name="neededValue"> second operand</param>
        /// <returns> if the first operand bigger than the second</returns>
        private static bool CheckBiggest(string valueForChecking, string neededValue)
        {
            int operand1;
            if (int.TryParse(neededValue, out int operand2))
            {
                operand1 = int.Parse(valueForChecking);
                if (operand1 > operand2)
                    return true;
            }
            else if (valueForChecking.CompareTo(neededValue) == 1)
                return true;
            return false;
        }

        /// <summary>
        /// Method to read test file and save its information in static fields
        /// </summary>
        /// <param name="path">path of test file</param>
        private static void ReadTestFile()
        {
            using (FileStream file = new FileStream(arg2, FileMode.Open, FileAccess.Read))
            using (StreamReader reader = new StreamReader(file))
            {
                firstLine = (reader.ReadLine()).Split(',');
                conditionNum = int.Parse(reader.ReadLine());
                conditionsArray = new string[conditionNum];
                for (int i = 0; i < conditionNum; i++)
                    conditionsArray[i] = reader.ReadLine();
            }
        }
    }
}