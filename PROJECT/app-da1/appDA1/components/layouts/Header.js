import React from "react";
import { View, Text, StyleSheet } from "react-native";

const Header = (props) => {
  const styles = StyleSheet.create({
    header: {
      width:props.Dimensions.width,
      height:(props.Dimensions.height*20)/100,
      backgroundColor: "#f2f2f2",
      paddingTop: 20,
      display: "flex",
      alignItems: "center",
      justifyContent: "center",
    },
    headerName: {
      fontSize: 24,
      fontWeight: "bold",
    },
    headerGroup: {
        fontSize: 21,
        fontWeight: "300",
      },
  });
  return (
    <View style={styles.header}>
      <View>
        <Text style={styles.headerName}>
            APP - MONITORING - FISH
        </Text>
      </View>
      <View>
        <Text style={styles.headerGroup}>
            Đồ án 1 - SPK
        </Text>
      </View>
    </View>
  );
};

export default Header;
