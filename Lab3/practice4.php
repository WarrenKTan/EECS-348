<style>
    header{
        font-size: 18pt;
        color: rgb(0, 0, 0);
    }

    table, th, td {
        font-size: 24;
        border:1px solid black;
        min-width: 48px;
        text-align: center;
    }
</style>
    
<?php

$size = $_POST['size'];

$outputTable = [[]];

echo "<header>";
for($i = 0; $i <= $size; $i++){
    $tmpTable = [];
    for($j = 0; $j <= $size; $j++){
        if ($i == 0){
            array_push($tmpTable, $j);
        }else if ($j == 0){
            array_push($tmpTable, $i);
        }else{
            array_push($tmpTable, $j * $i);
        }
    }
    array_push($outputTable, $tmpTable);
}
echo "</header>";

// odd ranges because tables don't print as I expect? ¯\_(ツ)_/¯
echo "<table>";
for ($i = 1; $i < count($outputTable); $i++){
    echo "<tr>";
    for ($j = 0; $j < count($outputTable) - 1; $j++){
        echo "<td>";
        if ($i == 1 || $j == 0){
            echo "<b>";
            echo $outputTable[$i][$j];
        }else{
            echo $outputTable[$i][$j];
        }
        echo "</td>";
    }
    echo "</tr>";
}
?>