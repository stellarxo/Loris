ALTER TABLE candidate ADD COLUMN DrexID VARCHAR(8) NULL, ADD UNIQUE INDEX `DrexID_UNIQUE` (`DrexID` ASC);