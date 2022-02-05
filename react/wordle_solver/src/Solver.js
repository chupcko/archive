import { useContext } from 'react';

import { Button, Stack, Box, Typography } from '@mui/material';

import { StoreContext } from './Store';

import RowEdit from './RowEdit';
import RowShow from './RowShow';

const Solver = (props) => {

  const { game, init } = useContext(StoreContext);

  return (
    <>
    {
      game.row != undefined && <>
        <Stack direction="row" spacing={ 1 } >
          <Button variant="contained" onClick={ () => { init(false); } } >
            Reset
          </Button>
          <Button variant="contained" onClick={ () => { init(true); } } color="error" >
            Do not CLICK!!!
          </Button>
        </Stack>
        {
          game.error && <Typography color="error" sx={ { paddingTop: 1 } } >{ game.error }</Typography>
        }
        <Stack spacing={ 1 } style={ { paddingTop: 10 } } >
          {
            game.rows.map(
              (row, index) => <Box key={ index }>
                {
                  !game.done && game.row == index ?
                    <RowEdit index={ index } />
                  :
                    <RowShow index={ index } />
                }
              </Box>
            )
          }
        </Stack>
      </>
    }
    </>
  );

};

export default Solver;
