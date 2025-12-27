(* Forward declarations. *)
procedure InitTable(Table: HashTablePtr); forward;
procedure InitBucket(var Bucket: NodePtr); forward;
function NewNode(Key: Key; Value: integer) : NodePtr; forward;
procedure InitNode(var Node: NodePtr; Key: Key; Value: integer); forward;
function GetHashedKey(Key: Key) : integer; forward;
function GetTargetBucket(HashedKey: integer; Capacity: integer) : integer; forward;
function IsFinalNode(Node: NodePtr) : boolean; forward;
function AreKeysEqual(Key1, Key2: Key): boolean; forward;
function KeyAlreadyExists(Table: HashTablePtr; Bucket: integer; Key: Key) : boolean; forward;
procedure AppendNode(Table: HashTablePtr; Key: Key; Value: integer); forward;

procedure InitTable(Table: HashTablePtr);
var
  I: integer;
  Buckets: HashTableBuckets;
begin
  for I := 1 to BucketInitialCapacity do
    InitBucket(Buckets[I]);
  Table^.Buckets := Buckets;
  Table^.Length := 0;
  Table^.Capacity := BucketInitialCapacity;
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
    HashedKey := HashedKey * 31 + OrdinalValue;
    Pos := Pos + 1;
  end;
  GetHashedKey := HashedKey; 
end;

function GetTargetBucket(HashedKey: integer; Capacity: integer) : integer;
begin
  GetTargetBucket := abs(HashedKey) mod Capacity + 1;
end;

function IsFinalNode(Node: NodePtr) : boolean;
begin
  IsFinalNode := Node^.NextNode = nil;
end;

function AreKeysEqual(Key1, Key2: Key): boolean;
var
  Index: integer;
  KeysMatching: boolean;
begin
  KeysMatching := true;
  Index := 1;
  while (Index <= KeyMaxLen) and (KeysMatching) do
  begin
    if Key1[Index] <> Key2[Index] then
      KeysMatching := false
    else
      Index := Index + 1;
  end;
  AreKeysEqual := KeysMatching;
end;

function KeyAlreadyExists(Table: HashTablePtr; Bucket: integer; Key: Key) : boolean;
var
  KeyFound: boolean;
  CurrentNode: NodePtr;
begin
  KeyFound := false;
  CurrentNode := Table^.Buckets[Bucket];
  while CurrentNode <> nil do
  begin
    if AreKeysEqual(CurrentNode^.Key, Key) then
    begin
      KeyFound := true;
      CurrentNode := nil; (* Exit loop. *)
    end
    else
      CurrentNode := CurrentNode^.NextNode;
  end;
  KeyAlreadyExists := KeyFound;
end;

procedure AppendNode(Table: HashTablePtr; Key: Key; Value: integer);
var
  BucketNumber: integer;
  CurrentNode: NodePtr;
begin
  BucketNumber := GetTargetBucket(GetHashedKey(Key), Table^.Capacity);
  if Table^.Buckets[BucketNumber] = nil then
    Table^.Buckets[BucketNumber] := NewNode(Key, Value)
  else
  begin
    if not KeyAlreadyExists(Table, BucketNumber, Key) then
    begin
      CurrentNode := Table^.Buckets[BucketNumber];
      while not IsFinalNode(CurrentNode) do
        CurrentNode := CurrentNode^.NextNode;
      CurrentNode^.NextNode := NewNode(Key, Value);
    end
    else
      writeln('Key already exists.');
  end;
end;
