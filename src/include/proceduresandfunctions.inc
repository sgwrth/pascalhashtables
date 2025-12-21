{ Forward declarations. }
procedure InitTable(var Table: HashTable); forward;
procedure InitBucket(var Bucket: NodePtr); forward;
function NewNode(Key: Key; Value: integer) : NodePtr; forward;
procedure InitNode(var Node: NodePtr; Key: Key; Value: integer); forward;
function GetHashedKey(Key: Key) : integer; forward;

procedure InitTable(var Table: HashTable);
var
  i: integer;
  Buckets: HashTableBuckets;
begin
  for i := 1 to BucketInitialCapacity do
    InitBucket(Buckets[i]);
  Table.Buckets := Buckets;
  Table.Length := 0;
  Table.Capacity := BucketInitialCapacity;
end;

procedure InitBucket(var Bucket: NodePtr);
begin
  Bucket := nil;
end;

function NewNode(Key: Key; Value: integer) : NodePtr;
var
  Node: NodePtr;
begin
  new(Node);
  InitNode(Node, Key, Value);
  NewNode := Node;
end;

procedure InitNode(var Node: NodePtr; Key: Key; Value: integer);
begin
  Node^.NextNode := nil;
  Node^.Key := Key;
  Node^.HashedKey := GetHashedKey(Key);
  Node^.Value := Value;
end;

function GetHashedKey(Key: Key) : integer;
var
  HashedKey: integer;
  OrdinalValue: integer;
  Pos: integer;
begin
  HashedKey := 0;
  Pos := 1;
  while (Pos <= KeyMaxLen) and (ord(Key[Pos]) <> 0) do
  begin
    OrdinalValue := ord(Key[Pos]);
    Pos := Pos + 1;
    HashedKey := HashedKey * 31;
    HashedKey := HashedKey + OrdinalValue;
  end;
  GetHashedKey := HashedKey; 
end;
