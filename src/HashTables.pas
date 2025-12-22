program HashTables;

(*$I include/constants.inc*)

(*$I include/types.inc*)

var
  Table: HashTablePtr;

(*$I include/proceduresandfunctions.inc*)

begin
  new(Table);
  InitTable(Table);
  Table^.Buckets[1] := NewNode('foo', 42);
  writeln(Table^.Buckets[1]^.Key);
  writeln(Table^.Buckets[1]^.Value:0);
  writeln(Table^.Buckets[1]^.HashedKey:0);
end.
