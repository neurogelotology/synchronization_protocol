function [upTTLtime, recStartTime] = getNlxTTL_demo(eventFilePath)
%{
    get sync TTL rise timestamps [s] from Neuralynx Events file
    recStartTime is the timestamp [s] of the first sample
    Parameters that may vary between device models
        TTL: event ID 21
        Bit position 1: IO 4

    Dagher & Ishiyama (2023)
%}
    % device dependent parameters
    TTLeventID = 21; % digital I/O of LabLynx
    bitpos = 1; % IO 4

    if ~nargin
        [eventFile,eventPath] = uigetfile('*.nev','Select Neuralynx Event file');
        eventFilePath = [eventPath,eventFile];
    end
    if ~eventFilePath
        return % user cancel
    end

    [TimeStamp, EventIDs, TTLs, EventStrings] = Nlx2MatEv_demo(eventFilePath);
    isTTLevent = EventIDs == TTLeventID;
    myBits = double(bitget(TTLs, bitpos));
    us2s = 1e-6;
    upTTLtime = double(TimeStamp(isTTLevent & myBits == 1))' * us2s;
    EventStrCell = cellstr(EventStrings);
    recStartTime = double(TimeStamp(strcmp(EventStrCell,'Starting Recording'))) * us2s;
end

function [TimeStamp, EventIDs, TTLs, EventStrings] = Nlx2MatEv_demo(FileName)

    HeaderSize = 2^14;
    ExtractRecord = logical([0 0 0 1 1 1 0 0 0 1 1]);
    RecordName = {'', '', '', 'TimeStamp', 'EventIDs', 'TTLs', '', '', '', 'Extras', 'EventStrings'};
    RecordSize = [2 2 2 8 2 2 2 2 2 4*8 1*128];
    RecordDataType = {'','','', 'uint64', 'uint16', 'uint16', '', '', '', 'uint32', 'char'};
    RecordMultiplicity = [0 0 0 1 1 1 0 0 0 8 128];
    fid = fopen(FileName);
    InitialSkip = 0;
    NumberOfRecords = inf;
    for ThisRecord = 1:numel(RecordSize)
        if ExtractRecord(ThisRecord)
            fseek(fid,HeaderSize + InitialSkip + sum(RecordSize(1:ThisRecord - 1)),'bof');
            eval([RecordName{ThisRecord}, ' = fread(fid, [' num2str(RecordMultiplicity(ThisRecord)) ', ' num2str(NumberOfRecords) '], ' ...
                '''' num2str(RecordMultiplicity(ThisRecord)) '*' RecordDataType{ThisRecord} '=>' RecordDataType{ThisRecord} ''', ', num2str(EverybodyElse(ThisRecord, RecordSize)), ');'])
            if isinf(NumberOfRecords) && strcmp(RecordName{ThisRecord}, 'TimeStamp')
                NumberOfRecords = numel(TimeStamp);
            end
        end
    end
    EventStrings = EventStrings';
    fclose(fid);

end

function E = EverybodyElse(MySelf, RecordSize)

    E = sum(RecordSize) - RecordSize(MySelf);

end