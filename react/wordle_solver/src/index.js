import { render } from 'react-dom';

import ThemeProvider from '@mui/material/styles/ThemeProvider';
import createTheme from '@mui/material/styles/createTheme';
import blue from '@mui/material/colors/blue';
import red from '@mui/material/colors/red';
import teal from '@mui/material/colors/teal';

import { StoreProvider } from './Store';

import App from './App';

const theme = createTheme(
  {
    palette: {
      primary: {
        main: teal[500]
      },
      secondary: {
        main: blue[500]
      },
      error: {
        main: red[500]
      }
    },
  }
);

render(
  <StoreProvider>
    <ThemeProvider theme={ theme } >
      <App />
    </ThemeProvider>
  </StoreProvider>,
  document.querySelector('#root')
);
